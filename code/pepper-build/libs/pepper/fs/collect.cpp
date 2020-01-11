#include <pepper/fs/collect.hpp>

#include <queue>

namespace pepper { namespace fs { 
  
  void collector::collect(const boost::filesystem::path &base, visitor &v) const
  {
    std::queue<boost::filesystem::path> candidates;

    candidates.push( boost::filesystem::path{ } );

    while ( candidates.size() > 0 )
    {
      const auto &curr = candidates.front();

      boost::filesystem::path full{ base / curr };

      v.visit(base, curr);

      if ( boost::filesystem::is_directory(full) ) 
      {
        //
        // NOTE The following style does not work for Ubuntu 15.04
        // 
        //  for (auto &entry : boost::filesystem::directory_iterator{ full }) { ... }
        //
        for ( boost::filesystem::directory_iterator it{ full }; it != boost::filesystem::directory_iterator{}; ++it)
        {
          candidates.push( curr / it->path().filename() );
        }
      }

      candidates.pop();
    }
  }

} }
