#ifndef __PEPPER_JSON_FIELD_OPT_H__
#define __PEPPER_JSON_FIELD_OPT_H__

#include "pepper/json/archive.hpp"
#include "pepper/json/field/base.hpp"

#include "pepper/opt.hpp"
#include "pepper/except.hpp"

#include <json/json.h>

namespace pepper { namespace json {

  /**
   * Optional Field
   */
  template <typename T, bool Public = true> class opt
    : public field
    , public pepper::opt<T>
  {        
    public:
      opt(object &obj, const std::string &name)
        : field{ obj, name }
      {
        // DO NOTHING
      }

      opt(json::meta &meta, const std::string &name)
        : field{ meta, name }
      {
        // DO NOTHING
      }

      virtual ~opt() = default;

    public:
      void operator=(const T &rhs)
      { 
        // NOTE Casting is necessary to prevent self-recursion
        *(static_cast<pepper::opt<T> *>(this)) = rhs;
      }

    public:
      virtual void load(const Json::Value &json) 
      {
        if ( json.isMember(name()) )
          archive<pepper::opt<T>>::load(json[name()], *this);
      }

      virtual void dump(Json::Value &json) const 
      {
        if ( this->is_initialized() )
          archive<pepper::opt<T>>::dump(json[name()], *this);
      }

      virtual void desc(Json::Value &json) const
      {
        if ( !Public ) 
        {
          // Do not describe if the field is not public
          return;
        }

        auto &node = json[name()];
        archive<T>::desc(node);

        std::string comment;

        comment += "/*";
        if ( _meta.desc.is_initialized() )
        {
          comment += " ";        
          comment += _meta.desc();
        }
        comment += " (optional)";
        comment += " */";

        node.setComment(comment, Json::commentAfterOnSameLine);
      }
  };

} }

#endif
