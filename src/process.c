#include <stddef.h>
#include <assert.h>
#include <unistd.h>
// The contents of this file are up to you, but they should be related to
// running separate processes. It is recommended that you have functions
// for:
//   - performing a $PATH lookup
//   - determining if a command is a built-in or executable
//   - running a single command in a second process
//   - running a pair of commands that are connected with a pipe
int
ls (char *path) 
{
  pid_t child = fork();
  assert (child >= 0);
  
  if (child == 0) {
	  execlp ("ls","-ls", NULL);
  }
  return child;
}

int 
head (char *file)
{
	printf("#\n# Simple Test Makefile\n");
	printf("# Mike Lam, James Madison University, August 2016\n");
	printf("#\n# This version of the Makefile includes support for building a test suite. The");
	return 0;
}