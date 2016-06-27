#include <stdlib.h>
#include <stdio.h>

#include "args_parser.h"
#include "tcp.h"
#include "http.h"
#include "rand.h"
#include "client.h"

int main(int argc, char *argv[])
{
  t_http_params params =
    {
      .port		= 4242,
      .token		= NULL,
      .token_len	= 12,
      .max_conn		= 1,
      .file		= NULL,
    };

  rand_init();

  parse_args(argc, argv, &params);
  args_logic(&params);


# ifdef DEBUG
  puts("============================");
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
  puts("============================");
# endif

  printf("serving at >> http://0.0.0.0:%d/%s <<\n", params.port, params.token);
  wait_for_client(handle_client, &params);
  return (EXIT_SUCCESS);
}
