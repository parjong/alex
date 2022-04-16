#include "build/monitor.h"
#include "build/record_tracer.h"

#include <string>
#include <iostream>

#include <assert.h>
#include <stdlib.h>
#include <getopt.h>

Terminator *run(const std::string& output, 
                char *path, 
                char * const argv[], 
                char * const envp[])
{
  Emit          emit(output);

  ExecTracee    tracee(path, argv, envp);
  RecordTracer  tracer(emit);

  Monitor       m(tracee, tracer);

  emit.init();

  return m.trace();
}

/**
 * Usage: <tool> <output> -- <path> <argv ...>
 */
int main(int argc, char * const argv[], char * const envp[])
{
  std::string *output_val = nullptr;

  static struct option long_opts[] =
  {
    { "output", required_argument,  0,  'o' },
    { 0,        0,                  0,  0   },
  };

  while ( 1 )
  {
    int opt = getopt_long(argc, argv, "o:", long_opts, NULL);

    if ( opt == -1 ) break;

    switch ( opt )
    {
      case 'o':
        assert( optarg != nullptr );
        assert( output_val == nullptr );

        output_val = new std::string(optarg);

        break;
      default:
        break;
    }
  }

  if ( output_val == nullptr )
  {
    std::cerr << "ERROR: --output should be specified" << std::endl;
    exit(EXIT_FAILURE);
  }

  /** Check the reamining arguments */
  char *u_path = *(argv + optind);
  char * const *u_argv = argv + optind + 1;
  char * const *u_envp = envp;

  run(*output_val, u_path, u_argv, u_envp)->terminate();

  return EXIT_FAILURE;
}
