#ifndef HTTP_H_
# define HTTP_H_

# include "netinit.h"
# include "args_parser.h"

int	handle_client(int sock, t_address *addr, t_http_params *params);

#endif
