#include <stdio.h>
#include <string.h>

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

      if (input != stdin)
        printf ("%s", buffer);
	  if (strncmp(buffer, "quit", 4) == 0) 
		break;
	  if (strncmp(buffer, "echo", 4) == 0)
		echo(&buffer[5]);
	  if (strncmp(buffer, "pwd", 3) == 0)
		pwd();
    }
  printf ("\n");
  hash_destroy ();
}
