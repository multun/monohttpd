#ifndef ARGS_H_
# define ARGS_H_

/*
**
** getopt:
**  argv: arguments of the program
**  argc: number of arguments
**  opts: options for the arguments to pull
**  optval: value of the argument pulled, if one
**
** opts is an array of chars where each letter can be followed
** by a colon if it requires a word argument
**
*/

int	getopt(char *argv[], int argc,
	       const char opts[], char **optval);

// current index of the option being processed by getopt
extern int	optind;


#endif
