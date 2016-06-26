#ifndef HTTP_H_
# define HTTP_H_

#include <stdio.h>

void	send_header(int sfd, char code[], char fields[], size_t size);
void	send_file_header(int sfd, char code[], char fname[], size_t fsize);
void	send_string(int sfd, char code[], char string[]);
void	send_file(int sfd, char code[], char path[]);

#endif
