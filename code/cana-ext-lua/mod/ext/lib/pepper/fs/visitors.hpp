#ifndef __PEPPER_FS_VISITORS_H__
#define __PEPPER_FS_VISITORS_H__

#include <pepper/pathname.hpp>
#include <pepper/fs/collect.hpp>

namespace pepper { namespace fs {

  struct globbing_visitor : public pepper::fs::visitor
  {
    private:
      const pepper::pathname::glob &_glob;

    public:
      globbing_visitor(const pepper::pathname::glob &glob) 
        : _glob( glob )
      {
      }
      virtual ~globbing_visitor() = default;
    
    private:
      std::vector<std::function <void (const boost::filesystem::path &, const boost::filesystem::path &)>> _functions;
    public:
      void add_function(std::function <void (const boost::filesystem::path &, const boost::filesystem::path &)> fn)
      {
        _functions.emplace_back(fn);
      }

    public:
      virtual void visit(const boost::filesystem::path &b, const boost::filesystem::path &r) 
      {
        if ( !_glob.match(r) )
          return;

        for (auto &func : _functions)
        {
          func(b, r);
        }
      }
  };

} } 

#endif
