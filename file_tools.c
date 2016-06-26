#include <stdio.h>
#include <stdlib.h>

#include "error.h"

size_t	fsize(FILE* fd)
{
  long int size;
  long init_pos;

  // probably more portable that fstat, which isn't POSIX

  WPERROR((init_pos = ftell(fd)), "ftell");
  WPERROR(fseek(fd, 0, SEEK_END), "fseek");
  WPERROR(size = ftell(fd), "ftell");
  WPERROR(fseek(fd, init_pos, SEEK_SET), "fseek");
  return size;
}

char	*getfname(char path[])
{
  char *fname, *cur;
  cur = fname = path;
  while (*cur)
    {
      if (*cur == '/')
	fname = cur;
      cur++;
    }
  fname++;
  if (!*fname)
    FAIL("path cannot end with a slash");
  return fname;
}
