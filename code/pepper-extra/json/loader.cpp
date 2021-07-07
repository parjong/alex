#include "pepper/json/loader.hpp"
#include "pepper/json/header.hpp"

#include "pepper/subst.hpp"

namespace 
{
  class json_rewritor
  {
    private:
      const pepper::subst &_subst;

    public:
      json_rewritor(const pepper::subst &subst)
        : _subst( subst ) 
      {
        // DO NOTHING
      }
      virtual ~json_rewritor() = default;

    private:
      void rewrite_val(Json::Value &value)
      {
        if ( !value.isString() )
          return;

        value = _subst.rewrite(value.asString());
      }

      void rewrite_obj(Json::Value &node)
      {
        for (const auto &k : node.getMemberNames())
        {
          rewrite( node[k] );
        }            
      }

      void rewrite_arr(Json::Value &node)
      {
        for (auto &child : node)
        {
          rewrite( child );
        }
      }

    public:
      void rewrite(Json::Value &node)
      {
        if ( node.isArray() )
          rewrite_arr(node);
        else if ( node.isObject() )
          rewrite_obj(node); 
        else
          rewrite_val(node);
      }
  };
}

namespace pepper { namespace json {

  loader::loader(const pepper::dict::base &dict)
    : _dict(dict)
  {

  }

  bool loader::load(const pepper::pathname::file &file, Json::Value &into) const
  {
    static pepper::logging::logger log{ "pepper.json.loader.load" };

    if ( !file.does_exist() )
    {
      return false;
    }

    auto load_fn = [&](std::istream &is)
    {
      is >> into;
    };

    file.open(load_fn);

    log.debug("load '%s' from the file", into);

    pepper::dict::layered dict{ _dict };

    // Read header
    pepper::json::header header;

    into >> header;

    auto set_fn = [&] (const js::dict<std::string> &vs)
    {
      for (auto it = vs.begin(); it != vs.end(); ++it)
      {
        dict.set(it->first, it->second);
      }
    };

    header.variables.map(set_fn);

    // Substitute
    pepper::subst subst{ dict };

    ::json_rewritor js_subst{ subst };

    js_subst.rewrite(into);

    log.debug("get '%s' after rewriting", into);
       
    return true;
  }

} }
