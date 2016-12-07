#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "source.h"


/* Exercise 3.1.a: Set string */
/* Parameters:
 * str: string to be assigned
 * Returns: pointer to the newly allocated string */
char *set_string(const char *str)
{
	char * retVal = malloc(sizeof(char)*(strlen(str) + 1));
	strcpy(retVal, str);
		
    return retVal;  
}

/* Exercise 3.1.b: Print vector *
 * Parameters:
 * dest: the existing string to be appended
 * src: new string to be appended 
 * Returns: pointer to the resulting string */
char *append_string(char *dest, const char *src)
{
	int i;
	char * str = malloc(sizeof(char)*(strlen(dest)+1));
	char * appStr = realloc(str, sizeof(char)*(strlen(dest)+strlen(src)+1));
	
	strncpy(appStr, dest, strlen(dest));
	strncpy(&(appStr[strlen(dest)]), src, strlen(src));
	strcpy(&(appStr[strlen(dest)+strlen(src)]), "\0");
    return appStr;
}

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
