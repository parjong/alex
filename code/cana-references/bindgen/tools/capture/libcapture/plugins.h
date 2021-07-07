#ifndef __CAPTURE_PLUGIN_H__
#define __CAPTURE_PLUGIN_H__

#include "libscan/plugin/consumer.h"
#include "libscan/plugin/matcher.h"

namespace capture {
  namespace consumer { 
    namespace record {
      class object : public tokens::plugin::consumer::object {
        private:
          std::vector<std::string> &out_;

        public:
          object(std::vector<std::string> &out) : out_(out) {
            // DO NOTHING
          }
        
        public:
          virtual void consume(const std::vector<std::string> &args) {
            out_.insert(std::end(out_), std::begin(args), std::end(args));
          }
      };

      class factory : public tokens::plugin::consumer::factory {
        private:
          std::vector<std::string> &out_;

        public:
          factory(std::vector<std::string> &out) : out_(out) {
            // DO NOTHING
          }

        public:
          virtual tokens::plugin::consumer::object *create(void) {
            return new object(out_);
          }
      };
    }
  }  
}

namespace capture {
  namespace matcher { 
    namespace record {
      class object : public tokens::plugin::matcher::object {
        private:
          std::vector<std::string> &out_;

        public:
          object(std::vector<std::string> &out) : out_(out) {
            // DO NOTHING
          }
        
        public:
          virtual void match(const boost::smatch &sm) {
            out_.push_back(sm[0]);
          }
      };

      class factory : public tokens::plugin::matcher::factory {
        private:
          std::vector<std::string> &out_;

        public:
          factory(std::vector<std::string> &out) : out_(out) {
            // DO NOTHING
          }

        public:
          virtual tokens::plugin::matcher::object *create(void) {
            return new object(out_);
          }
      };
    }
  }  
}

namespace capture {
  namespace consumer {
    namespace append {
      class object : public tokens::plugin::consumer::object {
        private:
          std::vector<std::string> &out_;
        public:
          object(std::vector<std::string> &out) : out_(out) {
            // DO NOTHING
          }
        public:
          virtual void consume(const std::vector<std::string> &args) {
            out_.push_back(args[1]);
          }
      };

      class factory : public tokens::plugin::consumer::factory {
        private:
          std::vector<std::string> &out_;
        public:
          factory(std::vector<std::string> &out) : out_(out) {
            // DO NOTHING
          }
        public:
          virtual tokens::plugin::consumer::object *create(void) {
            return new object(out_);
          }
      };
    }
  }
}

namespace capture {
  namespace consumer {
    namespace show {
      struct object : public tokens::plugin::consumer::object {
        virtual void consume(const std::vector<std::string> &args) {
          std::cout << "ARGS: " << args[1] << std::endl;
        }
      };

      struct factory : public tokens::plugin::consumer::factory {
        virtual tokens::plugin::consumer::object *create(void) {
          return new object();
        }
      };
    }
  }
}

namespace capture {
  namespace matcher {
    namespace show {
      struct object : public tokens::plugin::matcher::object {
        virtual void match(const boost::smatch &sm) {
          std::cout << "MATCHED: " << sm[1] << std::endl;
        }
      };

      struct factory : public tokens::plugin::matcher::factory {
        virtual tokens::plugin::matcher::object *create(void) {
          return new object();
        }
      };
    }
  }
}

namespace capture {
  namespace matcher {
    namespace append {
      class object : public tokens::plugin::matcher::object {
        private:
          std::vector<std::string> &out_;
        public:
          object(std::vector<std::string> &out) : out_(out) { 
            // DO NOTHING
          }
        public:
          virtual void match(const boost::smatch &sm) {
            out_.push_back(sm[1]);
          }
      };

      class factory : public tokens::plugin::matcher::factory {
        private:
          std::vector<std::string> &out_;
        public:
          factory(std::vector<std::string> &out) : out_(out) {
            // DO NOTHING
          }
        public:
          virtual tokens::plugin::matcher::object *create(void) {
            return new object(out_);
          }
      };
    }
  }
}


#endif
