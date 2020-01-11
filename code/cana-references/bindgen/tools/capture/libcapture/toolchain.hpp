#ifndef __LIBCAPTURE_TOOLCHAIN_HPP__
#define __LIBCAPTURE_TOOLCHAIN_HPP__

#include <map>
#include <string>

#include "libpepper/configure.hpp"

#include <boost/property_tree/xml_parser.hpp>

namespace capture {
  namespace compiler {
    class context {
      private:
        std::map<std::string, std::string> m_;
      public:
        context() = default;
        ~context() = default;

      public:
        void set(const std::string &path, const std::string &config) {
          m_[path] = config;
        }

        boost::optional<std::string> get(const std::string &path) {
          auto it = m_.find(path);

          if ( it != m_.end() ) {
            return it->second;
          }

          return boost::none;
        }
    };

    struct item : public configure::action<context> {
      virtual void extend(context &ctxt, const boost::property_tree::ptree &pt) {
        std::string path = pt.get<std::string>("path");
        std::string config = pt.get<std::string>("config");

        ctxt.set(path, config);
      }
    };

    void read_xml(const char *filename, context &cc) {
      boost::property_tree::ptree pt;
      boost::property_tree::read_xml(filename, pt);

      configure::configurator<capture::compiler::context> configurator;

      configurator.enroll("item", new capture::compiler::item());

      configurator.configure(cc, pt);
    }
  }
}

#endif
