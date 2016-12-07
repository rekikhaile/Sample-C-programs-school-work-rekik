#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "source.h"

/* Fills an array with random values */
void random_array(int *dest, int len)
{
    int i;

    for (i = 0; i < len; i++) {
        dest[i] = rand() % 100;
    }
}


int main()
{
    /* testing exercise 3.2. Feel free to modify this function */
    /* You may want to comment away calls that you have not yet implemented */
    int values[8];

    // initialize random number generator
    srand((unsigned)time(NULL));
    
    // randomize some content for the list
    random_array(values, 8);

    struct intList *list;
    int i;
    
    // Add 8 values to the linked list
    list = add_int(NULL, values[0]);
    printf("Adding following values to the list: %d ", values[0]);
    for (i = 1; i < 8; i++) {
        add_int(list, values[i]);
        printf("%d ", values[i]);
    }
    printf("\n");
    
    int findidx;
    for (i = 0; i < 3; i++) {
        findidx = rand() % 8;

        printf("Trying to find value %d from list -- ", values[findidx]);
        
        struct intList *ptr;
        ptr = find_int(list, values[findidx]);

        if (!ptr) {
            printf("did not find. There is an error\n");
            continue;
        }
        if (ptr->value != values[findidx]) {
            printf("found an item but with incorrect value %d\n", ptr->value);
            continue;
        }
        printf("found!\n");
    }

    list = remove_int(list, 100); // trying to remove non-existing item
    list = remove_int(list, values[3]); // removing existing item
    list = remove_int(list, values[1]); // removing existing item
    
    delete_list(list);
}
