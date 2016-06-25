
// for memset
#include <string.h>

#include "netinit.h"
#include "error.h"
#include "args_parser.h"

#define TCP_BACKLOG 5

static void close_socket(int fd)
{
  WPERROR(shutdown(fd, SHUT_WR), "shutdown");
  WPERROR(close(fd), "close");
}


void	config_socket(t_address *addr, int *sock, int port)
{
  const int true_opt = 1;

  WPERROR((*sock = socket(AF_INET, SOCK_STREAM, 0)) == -1, "socket");

  /* setting up the socket*/
  (*addr).sa_in.sin_family = AF_INET;
  (*addr).sa_in.sin_port = htons(port);
  (*addr).sa_in.sin_addr.s_addr = INADDR_ANY;

  memset(&((*addr).sa_in.sin_zero), 0, 8);

  WPERROR(setsockopt((*sock), SOL_SOCKET, SO_REUSEADDR, &true_opt, sizeof(int)),
	  "setsockopt");

  /* application de la configuration */
  WPERROR(bind(*sock, &((*addr).sa), sizeof(struct sockaddr)), "bind");

  /* mise en écoute du socket */
  WPERROR(listen(*sock, TCP_BACKLOG), "listen");
}

int	wait_for_client(
  int (*callback)(int, t_address*, t_http_params*),
  t_http_params *params)
{
  socklen_t	sin_size = sizeof(struct sockaddr_in);
  t_address	server_addr, client_addr;
  fd_set	readfds;
  int	sockfd, new_fd;

  config_socket(&server_addr, &sockfd, params->port);

  FD_ZERO(&readfds);
  FD_SET(sockfd, &readfds);

  puts("Waiting for someone to knock...");

  int stopping = 0;
  while (!stopping && select(sockfd+1, &readfds, NULL, NULL, NULL) >=0)
    {
      /* accept connexion */
      WPERROR(new_fd = accept(sockfd, &(client_addr.sa), &sin_size), "accept");
      //printf("Connexion from %s\n",inet_ntoa(client_addr.sa_in.sin_addr));
      stopping = callback(new_fd, &client_addr, params);
      close_socket(new_fd);
    }
  close_socket(sockfd);
  return 0;
}
