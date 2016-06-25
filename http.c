#include "netinit.h"
#include "args_parser.h"
#include "tcp.h"


// REMOVE ME WITH PRINTF
#include <stdio.h>

int	handle_client(int sock, t_address *addr, t_http_params *params)
{
  static int connections = 0;

  printf("%d %p %p", sock, addr, params);
  if (++connections >= params->max_conn)
    return (STOP_ACCEPTING);
  return (CONTINUE_ACCEPTING);
}
