int chartoint(char c)
{
  int res = c - '0';
  return ((res > 9 || res < 0) ? -1 : res);
}

int strtoint(int *res, const char s[])
{
  int digit, tres = 0;
  for (int i = 0; s[i] != '\0'; i++)
  {
    if ((digit = chartoint(s[i])) < 0)
      return (-1);
    tres *= 10;
    tres += digit;
  }
  *res = tres;
  return (0);
}
