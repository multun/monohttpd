#include <stdio.h>
#include <stdlib.h>

#include "error.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


size_t	fsize(int fd)
{
  struct stat fstats;

  WPERROR(fstat(fd, &fstats), "fstat");
  return fstats.st_size;
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
