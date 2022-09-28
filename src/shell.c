#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "builtins.h"
#include "hash.h"
#include "process.h"

// No command line can be more than 100 characters
#define MAXLENGTH 100

void
shell (FILE *input)
{
  hash_init (100);
  hash_insert ("?", "0");
  char buffer[MAXLENGTH];
  
  while (1)
    {
      // Print the cursor and get the next command entered
      printf ("$ ");
      memset (buffer, 0, sizeof (buffer));
      if (fgets (buffer, MAXLENGTH, input) == NULL)
        break;
	
	char *tmp = strdup (buffer);
	char *first = strtok (tmp, " ");
	char *sec = strtok (NULL, " ");
	char *arg[2];
	arg[0] = first;
	arg[1] = sec;

      if (input != stdin)
        printf ("%s", buffer);
    
	if (strncmp(first, "quit", 4) == 0) 
		break;
	else if (strncmp(arg[0], "echo", 4) == 0)
		echo(arg[1]);
	else if (strncmp(arg[0], "cd", 2) == 0)
        chdir (arg[1]);
	else if (strncmp(arg[0], "pwd", 3) == 0)
		pwd();
	else if (strncmp(arg[0], "ls", 2) == 0)
		ls(arg[1]);
	
	free (tmp);
    }
  printf ("\n");
  hash_destroy ();
}

