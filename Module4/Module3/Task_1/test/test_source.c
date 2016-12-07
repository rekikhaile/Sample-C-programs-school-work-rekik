#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/source.h"

START_TEST(test_set_string)
{
	char orig[] = "This is a test string! Not a very long one...";
	char *ptr;
	
	ptr = set_string(orig);
        fail_unless(ptr!=NULL, "[Task 3.1.a] Return value is NULL. String is not allocated properly\n");
        fail_unless(ptr != orig, "[Task 3.1.a] Return value equals str parameter. The string is not allocated from heap\n");
	fail_unless(!strcmp(ptr, orig), "[Task 3.1.a] Dynamically allocated string differs from original.\nOriginal: \"%s\".\nReturned: \"%s\".\n",
                orig, ptr);
	free(ptr);
}
END_TEST

START_TEST(test_append_string)
{
	char orig[] = "Another test:";
        char append[16];
        char ref[128];
        char *ptr;
        unsigned int len = (rand() % 4) + 8;
        
        for (unsigned int i = 0; i < len; i++) {
            append[i] = (rand() % ('Z' - 'A')) + 'A';
        }
        append[len] = 0;
        
        strcpy(ref, orig);
        strcat(ref, append);
        
	ptr = set_string(orig);
        fail_unless(ptr!=NULL, "[Task 3.1.b] Implement set_string first\n");
        fail_unless(ptr != orig, "[Task 3.1.b] Implement set_string first\n");       
        
        ptr = append_string(ptr, append);
        fail_unless(ptr!=NULL, "[Task 3.1.b] append_string returned NULL\n");
	fail_unless(!strcmp(ptr, ref), "Appending \"%s\" to \"%s\" failed. \nYour result: \"%s\". \nShould have been: \"%s\".\n",
                append, orig, ptr, ref);
	free(ptr);
}
END_TEST


int main(int argc, const char *argv[])
{
	srand((unsigned)time(NULL));
	Suite *s = suite_create("Test-3.1");

        /* TODO: define tests */
	tmc_register_test(s, test_set_string, "3.1.a");
	tmc_register_test(s, test_append_string, "3.1.b");
        
	return tmc_run_tests(argc, argv, s);
}
