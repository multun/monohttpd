#include <stdio.h>

#include "args.h"
#include "error.h"
#include "strconv.h"
#include "args_parser.h"

static const char HELP_MSG[] = "\
Use: monohttpd [OPTIONS] file\n\n\
Option\t\tDetails\n\
 -p <port>\t\tSets the port to use\n\
 -t <token>\t\tDefines the token to use\n\
 -l <token_len>\t\tDefines the random token length\n\
 -m <max>\t\tSets a maximum number of connexion attempts\n\
";

void print_help(void)
{
  // not a format string, but still safe to print
  printf(HELP_MSG);
}


// here because of the 25 lines limitation
void parse_nonpos(int argc, char *argv[], t_http_params *params)
{
  char	*argval;
  int curarg;
  while ((curarg = getopt(argv, argc, "hp:t:l:m:", &argval)) != -1)
    switch(curarg)
    {
    case 'p':
      STRTOINT(&(params->port), argval, "invalid port number");
      break;
    case 't':
      params->token = argval;
      break;
    case 'l':
      STRTOINT(&(params->token_len), argval, "invalid token length");
      break;
    case 'm':
      STRTOINT(&(params->max_conn), argval, "invalid max connection attempts");
      break;
    case 'h':
      print_help();
      exit(EXIT_SUCCESS);
    default:
      print_help();
      exit(EXIT_FAILURE);
    }
}


void parse_args(int argc, char *argv[], t_http_params *params)
{
  parse_nonpos(argc, argv, params);
  if (optind < argc)
  {
    if (optind + 1 != argc)
      FAIL("too many file specified");
    params->file = argv[optind];
  }
  else
    FAIL("missing file to send");
}
