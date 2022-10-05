#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <dirent.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <string.h>

static void usage (void);
int parse_args (int argc, char **argv, bool *file_all, bool *sizes, char **fname);

int
main (int argc, char *argv[])
{
  printf ("$");
  for (int i = 0; i < argc; i++)
    {
      printf (" %s", argv[i]);
    }

  bool a = false;
  bool s = false;
  DIR *dir = NULL;
  char *filename = NULL;

  if (parse_args(argc, argv, &a, &s, &filename) == -1) {
    usage();
    return EXIT_FAILURE;
  }
  dir = opendir(filename);
  if (dir == NULL) {
    return EXIT_FAILURE;
  }

  char d[100];
  getcwd(d, sizeof(d));
  strncat (d, "/", 2);
  if (argc == 2)
    strncat (d, argv[1], 10);
  if (argc == 3)
    strncat (d, argv[2], 10);

  int hid = 0;
  helper(a, s, dir, hid, d);
  return EXIT_SUCCESS;
}

void helper(bool a, bool s, DIR *dir, int hid, char *d) {
  char *directory = strtok (d, "\n");
  struct dirent *entry;
  int index = 0;
  while ((entry = readdir(dir)) != NULL) {
    struct stat st;
    char d2[strlen (directory) + strlen (entry->d_name) + 1];
    snprintf (d2, strlen (directory) + strlen (entry->d_name) + 2, "%s/%s", directory, entry->d_name);
    if (a == true && s == true) {
        stat(d2, &st);
        int size = st.st_size;
        printf("%d %s\n", size, entry -> d_name);
    } else if (s && !a) {
      if (hid > 1 && entry->d_name[0] != '.')
      {
        stat(d2, &st);
        int size = st.st_size;
        printf("%d %s\n", size, entry -> d_name);
      }
    } else if (!s && a) {
        printf("%s\n", entry -> d_name);
    } else {
       if (entry->d_name[0] != '.' && hid > 1) {
         printf("%s\n", entry -> d_name);
       }
    }
     hid++;
     index++;
  }
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

int
parse_args (int argc, char **argv, bool *a, bool *s, char **fname) {
  int c;
  while ((c = getopt(argc, argv, "a::s")) != -1) {
       switch(c) {
           case 's':
              *s = true;
              *fname = optarg;
              break;
           case 'a':
              *a = true;
              *fname = optarg;
              break;
           default:
              *s = false;
              *a = false;
              break;
       }
  }
  if (*fname == NULL) {
    char cw[100];
    if (getcwd(cw, sizeof(cw)) != NULL) {
      if (argc == 2)
        {
          strncat (cw, "/", 2);
          strncat (cw, argv[1], 10);
          *fname = strtok (cw, "\n");
        }
      else if (argc == 3)
        {
          strncat (cw, "/", 2);
          strncat (cw, argv[2], 10);
          *fname = strtok (cw, "\n");
        }
    }
  }
  return 0;
}