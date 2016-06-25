#ifndef ERROR_H_
# define ERROR_H_

# include <stdlib.h>
# include <stdio.h>


/*
** Prints a formatted error message and exits
*/

# define PERROR(FCT)						\
  do								\
  {								\
    fprintf (stderr, "Error at "__FILE__ ":%d => ", __LINE__);	\
    perror(FCT);						\
    exit(EXIT_FAILURE);						\
  } while (0)

# define WPERROR(CALL, NAME)			\
  if ((CALL))					\
    PERROR(NAME)

# define FAIL(format, ...)						      \
  do									      \
  {									      \
    fprintf (stderr, __FILE__ ":%d\t" format "\n", __LINE__,  ##__VA_ARGS__); \
    exit(EXIT_FAILURE);							      \
  } while(0)

# define LFAIL(...)							\
  do									\
  {									\
    fprintf (stderr, __VA_ARGS__);					\
    exit(EXIT_FAILURE);							\
  } while(0)
#endif
