#ifndef __CAPTURE_BACKEND_H__
#define __CAPTURE_BACKEND_H__

#include "libbuild/build.h"

#include "libscan/action/registry.h"
#include "libscan/scanner.h"

namespace capture {
  class backend {
    private:
      build::store &store_;

      pepper::named<tokens::plugin::consumer::factory> cr_;
      pepper::named<tokens::plugin::matcher::factory> mr_;

      tokens::action::registry::object ar_;

      tokens::scanner::object scanner_;

      std::vector<std::string> sources_;
      std::vector<std::string> outputs_;
      std::vector<std::string> options_;

    private:
      void enroll_consumers(void);     
      void enroll_matchers(void);      
      
      void configure_actions(const boost::property_tree::ptree &pt);      
      void configure_scanner(const boost::property_tree::ptree &pt);

    public:
      backend(build::store &store, const std::string &xml);
      ~backend() = default;

    private:
      void prepare(int cid);
      void process(int cid);

      void log_flow(int cid);
      void log_pp(int cid);

    public:
      void run(const std::string &exe, int cid);
  };
}

#endif
