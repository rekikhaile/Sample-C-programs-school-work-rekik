#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct intList {
	int value;
	struct intList *next;
};

struct intList *add_int(struct intList *first, int value);
struct intList *find_int(struct intList *first, int value);
struct intList *remove_int(struct intList *first, int value);
int delete_list(struct intList *first);
