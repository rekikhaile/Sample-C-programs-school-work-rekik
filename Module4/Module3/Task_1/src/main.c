#include <stdlib.h>
#include <stdio.h>
#include "source.h"

int main()
{
    /* testing exercise 3.1 */
    char *str1 = set_string("Ensimmäinen");
    if (!str1)
        return -1;
    
    str1 = append_string(str1, " Toinen");
    if (!str1)
        return -1;

    str1 = append_string(str1, " Kolmas");
    if (!str1)
        return -1;
    
    printf("%s\n", str1);
    free(str1);
    
    return 0;
}