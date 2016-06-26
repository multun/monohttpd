#include "http.h"
#include "tcp.h"
#include "args_parser.h"
#include "netinit.h"
#include "string.h"
#include "error.h"

int wait_request(int sock, t_http_params *params)
{
  const char prelude[] = "GET /";
  size_t token_size = strlen(params->token);
  size_t bufsize = sizeof(prelude) + token_size;
  char buffer[bufsize];

  blocking_recv(sock, buffer, bufsize + 1);
  //printf(">> %s", buffer);
  return !strncmp(prelude, buffer, sizeof(prelude) - 1) &&
    !strncmp(params->token, buffer + sizeof(prelude) - 1, token_size);
}


int	handle_client(int sock, t_address *addr, t_http_params *params)
{
  static int	connections = 0;

  UNUSED(addr);

  if (wait_request(sock, params))
    send_file(sock, "200 OK", params->file);
  else
    puts("wrong token");

  if (++connections >= params->max_conn)
    return (STOP_ACCEPTING);
  return (CONTINUE_ACCEPTING);
}
