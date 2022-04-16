#include "libcapture/backend.h"

#include <boost/filesystem.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/format.hpp>

#include "libscan/stream/vector.h"

#include <sys/types.h>
#include <sys/wait.h>

#include <string>
#include <map>

namespace {
  class buffer {
    private:
      char **ptr_;

    public:
      buffer() = delete;

      explicit buffer(const std::vector<std::string> &opts);
      explicit buffer(const std::map<std::string, std::string> &elems);
      ~buffer();

    public:
      char **get(void);
  };

  buffer::buffer(const std::vector<std::string> &opts) : ptr_(nullptr) {
    ptr_ = (char **) calloc(opts.size() + 1, sizeof(char *));

    char **curr = ptr_;

    for (auto it = opts.begin(); it != opts.end(); ++it) {
      *(curr++) = strdup(it->c_str());
    }

    *curr = nullptr;
  }

  buffer::buffer(const std::map<std::string, std::string> &elems) {
    ptr_ = (char **) calloc(elems.size() + 1, sizeof(char *));

    char **curr = ptr_;

    for (auto it = elems.begin(); it != elems.end(); ++it) {
      std::string elem = boost::str(boost::format("%s=%s") % it->first % it->second);

      *(curr++) = strdup(elem.c_str());
    }

    *curr = nullptr;
  }

  buffer::~buffer() {
    char **curr = ptr_;

    while ( *curr ) {
      free( *(curr++) );
    }

    free(ptr_);
  }

  char **buffer::get(void) { return ptr_; }
}

namespace {
  class arg {

  };

  class env {
    private:
      std::map<std::string, std::string> content_;

    public:
      env() = delete;
      explicit env(char **envp);
    public:
      ~env() = default;
  };

  env::env(char **envp) {
    char **curr = envp;

    while (*curr) {
      std::string elem( *(curr++) );

      std::size_t found = elem.find_first_of('=');

      if ( found == std::string::npos ) 
        throw std::runtime_error("Failed to find '='");      

      std::string k = elem.substr(0, found);
      std::string v = elem.substr(found + 1, std::string::npos);

      content_[k] = v;
    }
  }
}

namespace capture {
  void cmd_exec(const std::vector<std::string> &arg, const std::map<std::string, std::string> &env) { 
    ::buffer argv(arg);
    ::buffer envp(env);

    execve(argv.get()[0], argv.get(), envp.get());
  }

  void read_fd(int fd, std::string &out) {
    char buffer[4096];

    while ( ssize_t count = read(fd, buffer, sizeof(buffer)) ) {
      if ( count < -1 ) {
        throw std::runtime_error("read() failed");
      }

      for (ssize_t off = 0; off < count; ++off) {
        out.push_back(buffer[off]);
      }
    };
  }

  void cmd_run(const std::vector<std::string> &arg, const std::map<std::string, std::string> &env, 
               std::string &out, std::string &err) {
    pid_t pid = -1;

    int stdout_fds[2];
    int stderr_fds[2];

    if ( pipe(stdout_fds) == -1 ) {
      throw std::runtime_error("pipe() failed");
    }

    if ( pipe(stderr_fds) == -1 ) {
      throw std::runtime_error("pipe() failed");
    }

    pid = fork();

    if ( pid < 0 ) {
      throw std::runtime_error("fork() failed");
    }

    if ( pid == 0 ) {  
      dup2(stdout_fds[1], 1); //
      dup2(stderr_fds[1], 2); //
      
      close(stdout_fds[1]);
      close(stdout_fds[0]);

      close(stderr_fds[1]);
      close(stderr_fds[0]);

      cmd_exec(arg, env);

      throw std::runtime_error("cmd_exec() failed");
    } 

    close(stdout_fds[1]);
    close(stderr_fds[1]);

    read_fd(stdout_fds[0], out);
    read_fd(stderr_fds[0], err);

    close(stdout_fds[0]);
    close(stderr_fds[0]);

    int status;
   
    waitpid(pid, &status, 0);    
  }
}

namespace capture {
  void backend::enroll_consumers(void) {
    cr_.enroll("show", new consumer::show::factory());
    cr_.enroll("append", new consumer::append::factory(outputs_));
    cr_.enroll("record", new consumer::record::factory(options_));
  }

  void backend::enroll_matchers(void) {
    mr_.enroll("show", new matcher::show::factory());
    mr_.enroll("append", new matcher::append::factory(sources_));
    mr_.enroll("record", new matcher::record::factory(options_));
  }

  void backend::configure_actions(const boost::property_tree::ptree &pt) { 
    configure::configurator<tokens::action::registry::object> configurator;

    configurator.enroll("consume", new tokens::action::registry::configurators::consume(cr_));
    configurator.enroll("match", new tokens::action::registry::configurators::match(mr_));

    configurator.configure(ar_, pt.get_child("actions"));
  }

  void backend::configure_scanner(const boost::property_tree::ptree &pt) {
    configure::configurator<tokens::scanner::object> configurator;

    configurator.enroll("must", new tokens::scanner::configurators::must(ar_));
    configurator.enroll("may", new tokens::scanner::configurators::may(ar_));

    configurator.configure(scanner_, pt.get_child("scanner"));
  }

  backend::backend(build::store &store, const std::string &xml) : store_(store) {
    enroll_consumers();
    enroll_matchers();

    boost::property_tree::ptree pt;
    boost::property_tree::read_xml(xml, pt);

    configure_actions(pt);
    configure_scanner(pt);   
  }

  void backend::prepare(int cid) {
    // Get arguments
    std::vector<std::string> args;

    store_.get_command_arg(cid, args);

    tokens::stream::vector s(args);
    tokens::cursor c(s);

    // Skip argv[0]
    c.forward(1);

    // Scan the arguments
    scanner_.scan(c);

    // Logs on parse failure
    if ( s.lookup(0) ) {
      boost::format fmt("Failed to parse '%s' from the comand %d");

      store_.error(boost::str(fmt % s.lookup(0).get() % cid));
    }
  }

  void backend::log_flow(int cid) {
    std::string cwd = store_.get_command_cwd(cid);

    // Update flow table
    for (auto &source : sources_) {
      for (auto &output : outputs_) {
        boost::filesystem::path srcpath = boost::filesystem::canonical(source, cwd);
        boost::filesystem::path outpath = boost::filesystem::canonical(output, cwd);

        store_.set_command_flow(cid, srcpath.string(), outpath.string());
      }
    }
  }

  void backend::log_pp(int cid) {
    // Extract Preprocessed File
    std::string exe = store_.get_command_exe(cid);

    std::vector<std::string> pp_opts;

    pp_opts.push_back(exe);
    pp_opts.push_back("-E");
    pp_opts.insert(std::end(pp_opts), std::begin(options_), std::end(options_));

    //
    std::map<std::string, std::string> pp_env;
   
    env_init(pp_env);

    pp_env["LD_PRELOAD"] = "";

    //
    std::string pp_out;
    std::string pp_err;

    cmd_run(pp_opts, pp_env, pp_out, pp_err);

    store_.set_command_pp_opt(cid, pp_opts);
    store_.set_command_pp_out(cid, pp_out);
    store_.set_command_pp_err(cid, pp_err);
  }

  void backend::process(int cid) {
    log_flow(cid);
    log_pp(cid);
  }

  void backend::run(const std::string &exe, int cid) {
    prepare(cid);
    process(cid);
  } 
}

