#ifndef NETINIT_H_
# define NETINIT_H_


#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#ifdef __linux__
#include <linux/sockios.h>
#include <linux/limits.h>
#endif

typedef union u_address
{
  struct sockaddr sa;
  struct sockaddr_in sa_in;
} t_address;

#endif
