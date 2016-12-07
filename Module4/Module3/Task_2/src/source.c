#include "source.h"

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
			return first;
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
