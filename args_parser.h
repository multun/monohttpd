#ifndef ARGS_PARSER_H_
# define ARGS_PARSER_H_

typedef struct s_http_params
{
  int	port;
  char	*token;
  int	token_len;
  int	max_conn;
  char	*file;

} t_http_params;

void parse_args(int argc, char *argv[], t_http_params *params);

#endif
