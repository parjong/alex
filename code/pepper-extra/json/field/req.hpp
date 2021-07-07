#ifndef __PEPPER_JSON_FIELD_REQ_H__
#define __PEPPER_JSON_FIELD_REQ_H__

#include "pepper/json/archive.hpp"
#include "pepper/json/field/base.hpp"

#include "pepper/except.hpp"

#include <json/json.h>

namespace pepper { namespace json {

  template <typename T> class req
    : public field     
    , public T
  {        
    public:
      req(object &o, const std::string &name)
        : field{ o, name }
      {
        // DO NOTHING
      }

      req(json::meta &meta, const std::string &name)
        : field{ meta, name }
      {
        // DO NOTHING
      }

      virtual ~req() = default;

    public:
      template <typename U> void operator=(const U &rhs)
      {         
        *(static_cast<T *>(this)) = rhs;
      }
 
      const T &operator ()(void) const 
      {
        return *(static_cast<const T *>(this));
      }

    public:
      virtual void load(const Json::Value &json) 
      {
        if ( !json.isMember(name()) )        
          pepper::throw_exn("field '%s' is required, but not provided", name());  

        archive<T>::load(json[name()], *this);
      }

      virtual void dump(Json::Value &json) const 
      {               
        archive<T>::dump(json[name()], *this);
      }

      virtual void desc(Json::Value &json) const
      {
        auto &node = json[name()];

        archive<T>::desc(node);

        std::string comment;

        comment += "/*";
        if ( _meta.desc.is_initialized() )
        {
          comment += " ";        
          comment += _meta.desc();
        }
        comment += " (mandatory)";
        comment += " */";

        node.setComment(comment, Json::commentAfterOnSameLine);
      }
  };

} }

#endif
