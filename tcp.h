#ifndef TCP_H_
# define TCP_H_

# include "netinit.h"
# include "args_parser.h"

# define CONTINUE_ACCEPTING 0
# define STOP_ACCEPTING 1

void	blocking_recv(int sockfd, char *buf, size_t size);
void	blocking_send(int sockfd, const char *buf, size_t size);
void	config_socket(t_address *addr, int *sock, int port);
int	wait_for_client(
  int (*cb)(int, t_address*, t_http_params*),
  t_http_params *params);

#endif
