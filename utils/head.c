#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// You may assume that lines are no longer than 1024 bytes
#define LINELEN 1024

static void usage (void);

int
main (int argc, char *argv[])
{
  int c;
  long ret = 0;
  char *num = NULL;
  int fname = 0;
  while ((c = getopt (argc, argv, "n:c")) != -1)
    {
      switch (c)
        {
          case 'c':
            exit(EXIT_FAILURE);
          case 'n':
            num = optarg;
            ret = strtoul(num, NULL, 10);
            break;
          default:
            usage();
            exit(EXIT_FAILURE);
        }
        
    }
  
  if (argc != optind)
    {
      char *name = argv[optind];
      fname = open(name, O_RDONLY);
    }
    else {
      fname = STDIN_FILENO;
    }

  if (ret == 0)
  {
    ret = 5;
  }

  int count = 0;
  char buffer[LINELEN];
  read(fname, buffer, LINELEN);
  char *token = strtok(buffer, "\n");
  while (count < ret && token != NULL)
  {
    printf("%s\n", token);
    token = strtok(NULL, "\n");
    count++;
  }
  close(fname);
  exit(EXIT_SUCCESS);
}

static void
usage (void)
{
  printf ("head, prints the first few lines of a file\n");
  printf ("usage: head [FLAG] FILE\n");
  printf ("FLAG can be:\n");
  printf ("  -n N     show the first N lines (default 5)\n");
  printf ("If no FILE specified, read from STDIN\n");
}
