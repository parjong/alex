#include "emit/emit.h"

#include "emit/command.h"
#include "emit/failure.h"
#include "emit/code.h"

#include "query/mode.h"
#include "query/list_file.h"
#include "query/list_command.h"
#include "query/list_failure.h"
#include "query/show_file.h"
#include "query/show_command.h"
#include "query/exec.h"

#include <iostream>

#include <assert.h>
#include <getopt.h>

/**
 * Usage: <tool> --output <database> 
 */
int main(int argc, char **argv)
{
  //
  mode::manager manager;
  
  ListCommandMode listCommand;
  ListFailureMode listFailure;
  ListFileMode    listFile;
  ShowCommandMode showCommand;
  ShowFileMode    showFile;
  ExecuteMode     execCommand;

  manager.add("list-commands", listCommand);
  manager.add("list-failures", listFailure);
  manager.add("list-files", listFile);
  manager.add("show-command", showCommand);
  manager.add("show-file", showFile);
  manager.add("execute", execCommand);

  //  
  std::string *output_val = nullptr;  
  mode::action *action    = nullptr;

  static struct option long_opts[] =
  {
    { "output", required_argument,  0,  'o' },
    { "mode", required_argument,    0,  'm' },
    { 0,        0,                  0,  0   },  
  };

  while ( 1 )
  {
    int opt = getopt_long(argc, argv, "o:", long_opts, NULL);

    if ( opt == -1 ) break;    

    bool escape = false;

    switch (opt)
    {
      case 'o':
        assert( optarg != nullptr );
        assert( output_val == nullptr );

        output_val = new std::string(optarg);

        break;
      case 'm':
        assert( optarg != nullptr );
        
        action = manager.find(optarg);
        escape = true;
        break;

      default:
        break;
    }

    if ( escape ) break;
  }

  /** Check output */
  if ( output_val == nullptr )
  {
    std::cerr << "ERROR: --output should be specified" << std::endl;
    exit(-1);
  }

  if ( action == nullptr )
  {
    std::cerr << "ERROR: --mode should be specified" << std::endl;
    exit(-1);
  }

  Emit emit(*output_val);

  action->run(emit, argc - optind, argv + optind);

  return 0;
}
