#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void rand_init(void)
{
  srand(time(NULL));
}

char	rand_char(void)
{
  char alpha[]= \
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789";
  return alpha[rand() % (sizeof(alpha) - 1) ];
}

char	*rand_str(int size)
{
  char *str, *cur;
  int num = 0;

  cur = str = malloc(size+1);
  while (num++ < size)
    *cur++ = rand_char();

  str[size]='\0';
  return str;
}
