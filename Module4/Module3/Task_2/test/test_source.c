#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/source.h"

void random_array(int *dest, int len)
{
    int i;

    for (i = 0; i < len; i++) {
        dest[i] = rand() % 100;
    }
}

void release_list(struct intList *p)
{
    while (p) {
        struct intList *prev = p;
        p = p->next;
        free(prev);
    }
}

void pr_array(char *buf, int *arr, int n)
{
    char b[40];
    sprintf(buf, "{");
    while (n--) {
        sprintf(b, "%d", *arr++);
        if (n)
            strcat(b, ", ");
        strcat(buf, b);
    }
    strcat(buf, "}");
}


START_TEST(test_add_int)
{
    int i, len = 8;
    int values[10];
    struct intList *l, *ptr1, *ptr2;
    struct intList *other = NULL;
    char output[100];

    random_array(values, len);
    l = add_int(NULL, values[0]);
    fail_unless(l != NULL, "[Task 3.2.a] add_int returned NULL when trying to add value.\n");

    // Preventing solutions utilizing global variable
    other = add_int(NULL, 101);
    release_list(other);
    
    for (i = 1; i < len; i++) {
        ptr1 = add_int(l, values[i]);
        if (!ptr1) {
            release_list(l);
            fail("[Task 3.2.a] add_int returned NULL when trying to add multiple values.\n");
        }
        if (ptr1->value != values[i]) {
            release_list(l);
            fail("[Task 3.2.a] Adding new value %d, but returned list item has value: %d. Should return the added list item.\n",
                values[1], ptr1->value);
        }
        /*fail_unless(ptr1->value == values[i], "Adding new value %d, but returned list item has value: %d. Should return the added list item.\n",
                values[1], ptr1->value);*/
        if (ptr1->next) {
            release_list(l);
            fail("[Task 3.2.a] The next pointer should be NULL in the new list item.\n");
        }
        //fail_unless(!ptr1->next, "The next pointer should be NULL in the new list item.\n");
    }
    
    pr_array(output, values, len);
    
    ptr2 = l;
    for (i = 0; i < len; i++) {
        if (i < len - 1 && ptr2->next == NULL) {
            release_list(l);
            fail("[Task 3.2.a] After adding values %s, the %dth item incorrectly has NULL as next pointer\n",
                    output, i+1);
        }
        if (ptr2->value != values[i]) {
            release_list(l);
            fail("[Task 3.2.a] After adding values %s, the %dth item has value %d, should be %d\n",
                    output, i+1, ptr2->value, values[i]);
        }
        ptr2 = ptr2->next;
    }
    
    release_list(l);
}
END_TEST

struct intList *init_list(const int values[], int len) {

    struct intList *l;
    int i;
    
    l = add_int(NULL, values[0]);
    for (i = 1; i < len; i++) {
        add_int(l, values[i]);
    }
    return l;
}

int add_int_exists()
{
    struct intList *l;
    l = add_int(NULL, 1);
    if (l) {
        free(l);
        return 1;
    } else {
        return 0;
    }
}


START_TEST(test_find_int)
{
    int len = 8;
    int values[10];
    struct intList *l, *ptr;
    
    fail_unless(add_int_exists(), "[Task 3.2.b] Implement add_int first!\n");

    random_array(values, len);
    l  = init_list(values, len);

    char output[100];
    pr_array(output, values, len);
    
    int findidx;
    for (int i = 0; i < 3; i++) {
        findidx = rand() % len;

        ptr = find_int(l, values[findidx]);
        if (!ptr) {
            release_list(l);
            fail("[Task 3.2.b] After adding list %s, find_int did not find value %d, as it should have\n",
                    output, values[findidx]);
        }
        if (ptr->value != values[findidx]) {
            int value = ptr->value;
            release_list(l);
            fail("[Task 3.2.b] After adding list %s, find_int for %d returned item with value %d, should have been %d\n",
                    output, values[findidx], value, values[findidx]);
        }
    }

    ptr = find_int(l, 10000);
    if (ptr) {
        release_list(l);
        fail("[Task 3.2.b] After adding list %s, find_int for value 10000 should return NULL\n",
                output);
    }
    
    release_list(l);
}
END_TEST

int compare_list(struct intList *l, const int *values ,int len)
{
    struct intList *ptr;
    int i;
    ptr = l;
    for (i = 0; i < len; i++) {
	if (!ptr) return 1;
        if (ptr->value != values[i]) {
            return i;
        }
        ptr = ptr->next;
    }    
    return -1;
}

void print_list(char *buf, struct intList *l)
{
    char buf2[10];
    int count = 15;
    sprintf(buf, "{ ");
    while (l && count--) {
        sprintf(buf2, "%d ", l->value);
        strcat(buf, buf2);
        l = l->next;
    }
    strcat(buf, "}");
}


START_TEST(test_remove_int)
{
    int len = 9, fail = 0;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 5, 8};
    int values2[] = {1, 2, 3, 4, 5, 6, 5, 8};
    int values3[] = {1, 2, 3, 4, 6, 5, 8};
    int values4[] = {1, 2, 3, 4, 6, 5};
    int values5[] = {2, 3, 4, 6, 5, 8};
    struct intList *l, *retl;
    char output[80];
    
    fail_unless(add_int_exists(), "[Task 3.2.c] Implement add_int first!\n");
    
    l  = init_list(values, len);
    
    retl = remove_int(l, len);
    if (retl != l) {
	    release_list(l);
	    fail("[Task 3.2.c] Incorrect return value after removing non-existent item\n");
    }
    fail = compare_list(l, values, len);
    if (fail != -1) {
	    release_list(l);
	    fail("[Task 3.2.c] Removing of nonexistent item modified the linked list.\n");
    }
    
    l = remove_int(l, 7);
    print_list(output, l);
    fail = compare_list(l, values2, len - 1);
    if (fail != -1) {
        release_list(l);
        fail("[Task 3.2.c] Incorrect list after removing 7 from {1, 2, 3, 4, 5, 6, 7, 5, 8}. \nCurrent list: %s. \nShould be: { 1 2 3 4 5 6 5 8 }\n",
            output);
    }

    l = remove_int(l, 5);
    print_list(output, l);
    fail = compare_list(l, values3, len - 2);
    if (fail != -1) {
        release_list(l);
        fail("[Task 3.2.c] Incorrect list after removing 7 and 5 from {1, 2, 3, 4, 5, 6, 7, 5, 8}. \nCurrent list: %s. \nShould be: { 1 2 3 4 6 5 8 }\n",
            output);       
    }
    
/*    l = remove_int(l, 8);
    fail = compare_list(l, values4, len - 3);
    fail_unless(!fail, "Incorrect list after removal of last item.\n");*/

    l = remove_int(l, 1);
    print_list(output, l);
    fail = compare_list(l, values5, len - 3);
    if (fail != -1) {
        release_list(l);
        fail("[Task 3.2.c] Incorrect list after removing 7, 5, and 1 from {1, 2, 3, 4, 5, 6, 7, 5, 8}. \nCurrent list: %s. \nShould be: { 2 3 4 6 5 8 }",
                output);
    }

    release_list(l);
}
END_TEST


START_TEST(test_delete_list)
{
    int len = 100, i;
    int values[len];
    struct intList *l, *ptr;
    
    fail_unless(add_int_exists(), "[Task 3.2.d] Implement add_int first!\n");

    random_array(values, len);
    l  = init_list(values, len);
    ptr = l;
    for (i = 0; i < 99; i++) ptr = ptr->next;
    int ret = delete_list(l);
    if (!ret) {
        release_list(l);
        fail("[Task 3.2.d] delete_list should return 1 after properly implemented\n");
    }
}
END_TEST


int main(int argc, const char *argv[])
{

    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-3.2");

        /* TODO: define tests */
	tmc_register_test(s, test_add_int, "3.2.a");
	tmc_register_test(s, test_find_int, "3.2.b");
	tmc_register_test(s, test_remove_int, "3.2.c");
	tmc_register_test(s, test_delete_list, "3.2.d");        
        
	return tmc_run_tests(argc, argv, s);
}
