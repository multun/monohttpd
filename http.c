#define _GNU_SOURCE
#include <stdio.h>
#include <sys/sendfile.h>
#include <string.h>

// includes for open()
/*#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
*/
#include "netinit.h"
#include "tcp.h"
#include "error.h"
#include "file_tools.h"

void	send_header(int sfd, char code[], char fields[], size_t size)
{
  char		*header;
  ssize_t	header_size;

  WPERROR(
    header_size = asprintf(
      &header,
      "HTTP/1.0 %s\r\n"
      "%s"
      "Content-Length: %zu\r\n\r\n"
      , code, fields, size),
    "asprintf");

  blocking_send(sfd, header, header_size);
  free(header);
}


void	send_file_header(int sfd, char code[], char fname[], size_t fsize)
{
  char		*header;
  WPERROR(
    asprintf(
      &header,
      "Content-Type: application/octet-stream\r\n"
      "Content-Disposition: attachment; filename=%s\r\n",
      fname),
    "asprintf");

  send_header(sfd, code, header, fsize);
  free(header);
}


void	send_string(int sfd, char code[], char string[])
{
  size_t	len = strlen(string);

  send_header(sfd, code, "Content-Type: text/plain\r\n", len);
  blocking_send(sfd, string, len);
}


void	send_file(int sfd, char code[], char path[])
{
  FILE*		file;
  ssize_t	sent;
  size_t	size;

  WZPERROR(file = fopen(path, "r"), "fopen");
  size = fsize(file);

  send_file_header(sfd, code, getfname(path), size);

  WPERROR(
    sent = sendfile(sfd, fileno(file), NULL, size),
    "sendfile");
  WPERROR(fclose(file), "fclose");
}
