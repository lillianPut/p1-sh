#include <stddef.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
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
	const char *path = "./bin/head";
	char *const argv[] = {"head", file, NULL};
	pid_t child = 0;
	posix_spawn_file_actions_t action;
    posix_spawn_file_actions_init (&action);
    int status = posix_spawn (&child, path, &action, NULL, argv, NULL);
	return child;
}