#include "error.h"


static int islongopt(const char arg, const char opts[])
{
  for(int i = 0; ; i++)
  {
    if (!opts[i])
      return -1;
    if (opts[i] == arg)
      return (opts[i + 1] == ':');
  }
}

/*
**
** getopt:
**  argv: arguments of the program
**  argc: number of arguments
**  opts: options for the arguments to pull
**  optval: value of the argument pulled, if one
**
** opts is an array of chars where each letter can be followed
** by a colon if it requires a word argument
**
*/

// current index of the option being processed
int	optind = 1; // skip program name

static int ensure_valid(int *i, char *argv[], int argc)
{
  char is_valid = 0;
  while (!is_valid)
  {
    if (*i == 0)
    {
      if (optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '-')
	return (-1);
      *i = 1;
    }
    if (argv[optind][*i] == '\0')
    {
      optind++;
      *i = 0;
    }
    else
      is_valid = 1;
  }
  return (0);
}

int	getopt(char *argv[], int argc,
	       char opts[], char **optval)
{
  static int i = 0;
  int char_type;

  if (ensure_valid(&i, argv, argc) < 0)
    return (-1);

  char	argchar = argv[optind][i];

  if ((char_type = islongopt(argchar, opts)) > 0)
  {
    if (argv[optind][i+1] != '\0')
      FAIL("option %c cannot be followed by other flags", argchar);
    if (optind >= argc)
      FAIL("cannot pull argument for option %c", argchar);
    *optval = argv[++optind];
    optind++;
    i = 0;
  }
  else if (char_type < 0)
    return '?';
  else
    i++;
  return (argchar);
}
