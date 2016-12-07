#include "cmdline.h"


/* Parses a string into tokens (command line parameters) separated by space
 * Builds a dynamically allocated array of strings. Pointer to the array is
 * stored in variable pointed by argv.
 * 
 * Parameters:
 * argv: pointer to the variable that will store the string array
 * input: the string to be parsed (the original string can be modified, if needed)
 * 
 * Returns:
 * number of space-separated tokens in the string */
int parse_cmdline(char ***argv, char *input)
{
}


/* Finds command line options starting with '-' from the array of command line
 * parameters. Builds a new array of structures based for storing the command
 * line options.
 * 
 * Parameters:
 * argc: number of elements in argv (array of strings)
 * argv: array of strings representing command line parameters
 * 
 * Returns:
 * array of struct command records that hold the command line options and
 * their parameters. */
struct command *find_options(int argc, char **argv)
{
return NULL;   // replace this
}
