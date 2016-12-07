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

/* Exercise 3.2.a: Add Integer */
/* Parameters:
 * first: start of the linked list
 * value: integer to be added to linked list
 * Returns: pointer to the newly added node in the linked list */
struct intList *add_int(struct intList *first, int value) {
	if(first == NULL)
	{
		struct intList *list;
		list = (struct intList*)malloc(sizeof(struct intList));
		if(list == NULL)
			return NULL;
		list->value = value;
		list->next = NULL;
		return list;
	}
	else
	{
		struct intList *list;
		list = first;
		while(list->next != NULL)
		{
			list = list -> next;
		}
		list->next = (struct intList*)malloc(sizeof(struct intList));
		if(list->next == NULL)
			return NULL;
		list->next->value = value;
		list->next->next = NULL;

		return list->next;   // replace this
	}
}

/* Exercise 3.2.b: Find Integer */
/* Parameters:
 * first: first element in the linked list
 * value: value to be found
 * Returns: Pointer to the first instance of 'value', or NULL if not found */
struct intList *find_int(struct intList *first, int value) {
	while(first->next != NULL)
	{
		if(first->value == value)
		{
			return first;
		}
		else
			first = first->next;
	}
	if(first->value == value)
		return first;
		
	return NULL;
}


/* Exercise 3.2.c: Remove Integer */
/* Parameters:
 * first: The first element in list
 * value: value to be removed
 * Returns: Pointer to the first element in the list */
struct intList *remove_int(struct intList *first, int value) {
	if(first == NULL)
		return NULL;
	struct intList *current= first;
	struct intList *prev= first;
	
	if(first->value != value)
	{
		while(current->next != NULL && current->value != value)
		{
			prev = current;
			current = current->next;
		}
		
		if(current->value == value)
		{
			prev->next = current->next;
			free(current);
			return first;
		}
		else
			return NULL;
	}
	else
	{
		struct intList *newFirst = current->next;
		free(first);
		return newFirst;
	}
		
}
/* Exercise 3.2.d: Delete list */
/* Parameters:
 * first: first element in linked list
 * Returns: 1, when list has been deleted */
int delete_list(struct intList *first) {
	while(first != NULL)
	{
	first = remove_int(first, first->value);
	}
	return 1;
}
