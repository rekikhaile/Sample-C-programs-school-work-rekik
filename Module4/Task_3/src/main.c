#include <stdio.h>
#include <stdlib.h>
#include "cmdline.h"

int main(void)
{
    /* Hint: if you have implemented only part of the functions,
       add comments around those that you didn't yet implement.
       Feel free to modify this function as you wish. It is not checked
       by the tester.*/

    char **args = NULL;
    char cmdline[] = "cmdline -s 20 -r -t parameter -p 20 filename";
    int count = parse_cmdline(&args, cmdline);
    
    struct command *cmds;
    cmds = find_options(count, args);
    
    /* If implementing parse_cmdline is problematic, you can directly move
       to implementing find_options by taking the below code into use
       and commenting away the above code */
    /* const char *args[] = { "cmdline", "-s", "20", "-r", "-t", "parameter", "-p",
        "20", "filename" };    
    cmds = find_options(sizeof(args) / sizeof(char *), args); */
    
    /* Print the options that have been parsed */
    int ci = 0;
    while (cmds && cmds[ci].com) {
        printf("option: %c  ", cmds[ci].com);
        if (cmds[ci].param)
            printf("parameter: %s\n", cmds[ci].param);
        else
            printf("no parameter\n");
        ci++;
    }
    return EXIT_SUCCESS;
}
