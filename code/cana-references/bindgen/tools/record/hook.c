#include <stdio.h>
#include <stdlib.h>

static FILE *fp = NULL;

static void fini(int code, void *args)
{
  fprintf(fp, "Exited by %d\n", code);
}

static void init(int argc, char **argv, char **envp)
{
  fp = fopen("log.txt", "a");

  fprintf(fp, "Start\n");
  fprintf(fp, "argc = %d\n", argc);

  for (int i = 0; i < argc; ++i) {
    fprintf(fp, "argv[%05d] = '%s'\n", i, argv[i]);
  }

  on_exit(fini, NULL);
}

__attribute__ ((section(".init_array"))) typeof(init) *__init = init;
