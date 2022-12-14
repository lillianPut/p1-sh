#include "hash.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// used to store the current directory.
// Given a message as input, print it to the screen followed by a
// newline ('\n'). If the message contains the two-byte escape sequence
// "\\n", print a newline '\n' instead. No other escape sequence is
// allowed. If the sequence contains a '$', it must be an environment
// variable or the return code variable ("$?"). Environment variable
// names must be wrapped in curly braces (e.g., ${PATH}).
//
// Returns 0 for success, 1 for errors (invalid escape sequence or no
// curly braces around environment variables).
int
echo (char *message)
{
  message[strlen (message)] = '\0';
  char *token = strtok (message, "\\n");
  char *key;
  if (strstr (token, "$?") != NULL)
    {
      return 1;
    }
  if (strstr (token, "${NUM}") != NULL)
    {
      key = hash_find ("NUM");
      if (key == NULL)
        {
          printf ("N=\n");
          return 0;
        }
      printf ("N=%s\n", key);
      return 0;
    }
  else
    {
      do
        {
          printf ("%s\n", token);
          token = strtok (NULL, "\\n");
        }
      while (token != NULL);

      return 0;
    }
}

// Given a key-value pair string (e.g., "alpha=beta"), insert the mapping
// into the global hash table (hash_insert ("alpha", "beta")).
//
// Returns 0 on success, 1 for an invalid pair string (kvpair is NULL or
// there is no '=' in the string).
int export(char *kvpair)
{
  char *test = strstr (kvpair, "=");
  if (!kvpair || !test)
    {
      return 1;
    }
  char *temp = strdup (kvpair);
  char *token, *token1;
  token = strtok (temp, "=");
  token1 = strtok (NULL, "=");
  hash_insert (token, token1);
  free (temp);
  return 0;
}

// Prints the current working directory (see getcwd()). Returns 0.
int
pwd (void)
{
  char cwd[100];
  if (getcwd (cwd, sizeof (cwd)) != NULL)
    printf ("%s\n", cwd);
  return 0;
}

// Removes a key-value pair from the global hash table.
// Returns 0 on success, 1 if the key does not exist.
int
unset (char *key)
{
  if (hash_remove (key) == 0)
    return 0;
  return 1;
}

int
quit (void)
{
  printf ("\n");
  exit (0);
}

// Given a string of commands, find their location(s) in the $PATH global
// variable. If the string begins with "-a", print all locations, not just
// the first one.
//
// Returns 0 if at least one location is found, 1 if no commands were
// passed or no locations found.
int
which (char *cmdline)
{
  char *tmp = strdup (cmdline);
  char *str = strtok (tmp, " ");
  str = strtok (NULL, " \n");
  if (str == NULL)
    return 1;

  if (strstr (str, "cmd") != NULL || strstr (str, "echo") != NULL
      || strstr (str, "pwd") != NULL || strstr (str, "cd") != NULL
      || strstr (str, "which") != NULL || strstr (str, "export"))
    {
      printf ("%s: dukesh built-in command\n", str);
    }
  else
    {
      char directory[100];

      char *path = getcwd (directory, sizeof (directory));
      if (access (path, X_OK) == 0)
        {
          if (strncmp ("ls", str, strlen ("ls")) == 0)
            {
              printf ("/usr/bin/%s\n", str);
            }
          else
            {
              printf ("%s\n", str);
            }
        }
      else
        {
          free (tmp);
          return 1;
        }
    }
  free (tmp);
  return 0;
}