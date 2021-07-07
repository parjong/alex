#include "build/gcc_plugin.h"
#include "build/gcc_arity.h"
#include "build/gcc_option.h"
#include "build/gcc_options.h"
#include "build/gcc_utils.h"
#include "build/gcc_parser.h"
#include "build/FrontendActionRunner.h"

#include "emit/failure.h"
#include "emit/code.h"

#include "command_runner.h"

#include <memory>

#include <boost/algorithm/string/predicate.hpp>

#include <clang/Frontend/FrontendActions.h>

/**
 *
 */
static std::string make_absolute(const std::string& cwd, const std::string& path)
{
  if ( boost::algorithm::starts_with(path, "/") )
  {
    return cwd;
  }

  return cwd + "/" + path;
}

/**
 *
 */
class GCCFailureRecorder : public GCCCmdlineParser::Hook
{
  public:
    GCCFailureRecorder(Emit& emit, hiberlite::sqlid_t id) 
      : emit_(emit), id_(id)
    { 
      // Do NOTHING
    }
    virtual ~GCCFailureRecorder()
    {
      // Do NOTHING
    }
  private:
    Emit& emit_;    
    hiberlite::sqlid_t id_;
  public:
    virtual void accept(const std::string& token)
    {
      /** Returns (otherwise) */
      Failure failure(id_, token);

      emit_.commit(failure);
    }
};

/**
 *
 */
GCCPlugin::GCCPlugin(Emit& emit) 
  : emit_(emit) 
{ 
  // Do NOTHING
}

GCCPlugin::~GCCPlugin() { }

void GCCPlugin::run(hiberlite::sqlid_t id, const Command& cmd)
{
  if ( !boost::algorithm::ends_with(cmd.exe(), "gcc") )
  {
    return;
  }

  GCCCmdlineParser parser;

  parser.add(new GCCFailureRecorder(emit_, id));

  // Parse options
  std::unique_ptr<GNUOptions> options( parser.parse(emit_, id, cmd) );

  // Get Sources
  std::vector<std::string> sources;

  extrSourcesFromGNUOptions(sources, *options);

  // Get Options for PP 
  GNUOptions pp_options;

  extrPPOptionsFromGNUOptions(pp_options, *options);

  for (const std::string& source : sources)
  { 
    FILE *fp = tmpfile();

    // Construct the absolute path
    std::string absolute = make_absolute(cmd.cwd(), source);

    // Commit the source code (original)
    Code base(id, absolute);

    emit_.commit(base);

    // Construct the preprocessing command-line
    std::vector<std::string> pp_arg;
      
    pp_arg.push_back(cmd.exe());
    {
      GNUTokenExtractor extr(pp_arg);
      pp_options.accept(extr);
    }
    pp_arg.push_back("-E");
    pp_arg.push_back(source);

    // Execute the preprocessing command-line
    {
      ForkCommandRunner runner;
    
      runner.redirectOutput(fp);
      runner.run(cmd.cwd(), cmd.exe(), pp_arg, cmd.env());
    }

    // Commit the source code (preprocessed)
    Code code(id, fp);

    emit_.commit(code);
 
    //
    fclose(fp);
  }
}
