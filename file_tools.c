#include <stdio.h>
#include <stdlib.h>

#include "error.h"

long int	fsize(FILE* fd)
{
  long int size;
  long init_pos;

  // probably more portable that fstat, which isn't POSIX

  if(fd != NULL)
    {
      WPERROR((init_pos = ftell(fd)), "ftell");
      WPERROR(fseek(fd, 0, SEEK_END), "fseek");
      WPERROR(((size = ftell(fd)) == -1), "ftell");
      WPERROR(fseek(fd, init_pos, SEEK_SET), "fseek");
      return size;
    }
  else
    return -1;
}
