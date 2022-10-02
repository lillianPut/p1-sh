#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

static void usage (void);

int
main (int argc, char *argv[])
{
  chdir(argv[1]);
  pid_t child;
  child = fork();
  if (child == 0) 
	  execlp ("ls", "-ls", (char *) NULL);
  return EXIT_SUCCESS;
}

static void
usage (void)
{
  printf ("ls, list directory contents\n");
  printf ("usage: ls [FLAG ...] [DIR]\n");
  printf ("FLAG is one or more of:\n");
  printf ("  -a       list all files (even hidden ones)\n");
  printf ("  -s       list file sizes\n");
  printf ("If no DIR specified, list current directory contents\n");
}
