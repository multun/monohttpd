#include <sys/types.h>
#include <ifaddrs.h>
#include "netinit.h"
#include <netinet/in.h>
#include <net/if.h>
#include "error.h"
// no need to free the returned ip
char	*getfirstip(void)
{
  struct ifaddrs *addrs, *tmp;
  char	*addr = NULL;

  getifaddrs(&addrs);
  tmp = addrs;

  while (tmp)
  {
    if (tmp->ifa_addr &&
	tmp->ifa_addr->sa_family == AF_INET &&
	(tmp->ifa_flags & (IFF_RUNNING)) &&
	!(tmp->ifa_flags & (IFF_LOOPBACK)))
    {
      struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
       addr = inet_ntoa(pAddr->sin_addr);
       break;
    }
    tmp = tmp->ifa_next;
  }
  freeifaddrs(addrs);
  return (addr);
}

char	*getip(void)
{
  char *ip = getfirstip();
  if (!ip)
  {
    WARN("Couldn't find a running non-loopback interface");
    ip = "127.0.0.1";
  }
  return ip;
}
