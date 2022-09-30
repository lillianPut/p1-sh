#include <stdio.h>
#include <stdlib.h>

static void usage (void);

int
main (int argc, char *argv[], char *envp[])
{
  if (argc == 1)
  {
    char *s = getenv("PATH");
    printf("PATH=%s\n", s);
  }
  return EXIT_SUCCESS;
}

static void
usage (void)
{
  printf ("env, set environment variables and execute program\n");
  printf ("usage: env [name=value ...] PROG ARGS\n");
}

