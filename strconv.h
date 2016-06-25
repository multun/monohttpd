#ifndef STRCONV_H_
# define STRCONV_H_

// for the FAIL macro
#include "error.h"

// returns -1 if conversion failed, the binary digit otherwise
int chartoint(char);

// returns -1 if conversion failed, 0 otherwise
int strtoint(int*, const char*);

# define STRTOINT(IP, S, MSG)			\
  if(strtoint(IP, S) < 0)			\
    FAIL(MSG)

#endif
