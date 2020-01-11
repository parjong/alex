#ifndef __LIBSCAN_ACTION_REGISTRY_H__
#define __LIBSCAN_ACTION_REGISTRY_H__

#include "libpepper/named.hpp"
#include "libpepper/named_factory.hpp"
#include "libpepper/configure.hpp"

#include "libcapture/plugins.h"

#include "libscan/action/must.h"
#include "libscan/action/may.h"

namespace tokens {
  namespace action {
    namespace registry {
      struct object {
        pepper::named_factory<must::object>  must_;
        pepper::named_factory<may::object>   may_;
      };

      namespace configurators {
        class consume : public configure::action<object> {
          private:
            const pepper::named<plugin::consumer::factory> &cr_;

          public:
            consume(const pepper::named<plugin::consumer::factory> &cr);
            virtual ~consume() = default;
          public:
            virtual void extend(object &r, const boost::property_tree::ptree &pt);
        };

        class match : public configure::action<object> {
          private:
            const pepper::named<plugin::matcher::factory> &mr_;

          public:
            match(const pepper::named<plugin::matcher::factory> &mr);
            virtual ~match() = default;
          public:
            virtual void extend(object &r, const boost::property_tree::ptree &pt);
        }; 
      }
    }
  }
}

#endif
