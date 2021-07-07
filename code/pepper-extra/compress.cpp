#include "pepper/compress.hpp"

#include <archive.h>
#include <archive_entry.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace {

  struct visitor : public pepper::pathname::visitor::base
  {
    struct archive *_ar;

    visitor(struct archive *ar) : _ar{ ar }
    {
      // DO NOTHING
    }

    virtual ~visitor() = default;

    struct archive_entry *create_entry(const pepper::pathname::dir &base, const pepper::pathname::relative::base &relative) 
    {
      const boost::filesystem::path fullpath = base.path() / relative.path();

      struct stat st;

      stat( fullpath.string().c_str(), &st );

      struct archive_entry *entry = archive_entry_new();
      
      archive_entry_copy_stat( entry, &st );
      archive_entry_set_pathname( entry, relative.path().string().c_str() );

      archive_write_header( _ar, entry );

      return entry;
    }

    virtual void visit(const pepper::pathname::dir &base, const pepper::pathname::relative::file &file) 
    {      
      const boost::filesystem::path fullpath = base.path() / file.path();

      struct archive_entry *entry = create_entry( base, file );
      
      int fd = open( fullpath.string().c_str(), O_RDONLY );

      char data_buf[4096];
      int  data_len = 0;

      do 
      {
        data_len = read(fd, data_buf, sizeof(data_buf));
        archive_write_data( _ar, data_buf, data_len );
      }
      while ( data_len > 0 );

      close(fd);

      archive_entry_free( entry );
    }

    virtual bool visit(const pepper::pathname::dir &base, const pepper::pathname::relative::dir  &dir) 
    {
      struct archive_entry *entry = create_entry( base, dir );

      archive_entry_free( entry );
      
      return true;
    }
  };

  class libarchive_backend : public pepper::compress::backend
  {
    private:
      struct archive *_ar;

    public:
      libarchive_backend(const std::string &name) : _ar{ nullptr }
      {      
        _ar = archive_write_new();

        archive_write_set_format_zip( _ar );
        archive_write_open_filename( _ar, name.c_str() );
      }

    public:
      virtual ~libarchive_backend()
      {
        archive_write_close( _ar );
        archive_write_free( _ar );
      }

    public:
      void add_recursively( const pepper::pathname::dir &r ) const
      {
        visitor v{ _ar };

        r.accept(v);
      }
  };

}

namespace pepper { namespace compress {

  archive::archive(const pepper::pathname::file &output) 
    : _backend{ new ::libarchive_backend{output.path().string()} }
  {
    // DO NOTHING
  }

  void archive::add_recursively(const pepper::pathname::dir &r) const
  {
    _backend->add_recursively(r);
  }

} } 
