#include <stdlib.h>
#include <stdio.h>

#include "args_parser.h"
#include "tcp.h"
#include "http.h"

int main(int argc, char *argv[])
{
  t_http_params params;
  params.port		= 4242;
  params.token		= NULL;
  params.token_len	= 12;
  params.max_conn	= 1;
  params.file		= NULL;

  parse_args(argc, argv, &params);


# ifdef DEBUG
  printf("\
port\t\t%d\n\
token\t\t%s\n\
token_len\t%d\n\
max_conn\t%d\n\
file\t\t%s\n",
	 params.port,
	 params.token,
	 params.token_len,
	 params.max_conn,
	 params.file);
# endif

  wait_for_client(handle_client, &params);

  return (EXIT_SUCCESS);
}
