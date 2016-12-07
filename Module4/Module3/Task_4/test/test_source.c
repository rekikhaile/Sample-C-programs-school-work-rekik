#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "../src/source.h"

void release_memory(Students *s) {
    unsigned int i;
    if (s->array) {
        for (i = 0; i < s->count; i++) {
            Student *st = &(s->array[i]);
            if (st->name)
                free(st->name);
            if (st->points)
                free(st->points);
        }
        free(s->array);
    }
}

START_TEST(test_create_student) {
    Students reg;
    //assert(reg != NULL);
    reg.count = 0;
    reg.array = NULL;
    char buf[160];

    //char *name = malloc(strlen("Teemu Teekkari") + 1);
    //strcpy(name, "Teemu Teekkari");
    char *name = "Teemu Teekkari";

    Student *s1 = create_student(&reg, name, "00000A", 20, "ELEC-A1100");
    fail_unless(s1 != NULL, "[Task 3.4.a] create_student returned NULL.\n");

    if (strcmp(name, s1->name)) {
        sprintf(buf, "[Task 3.4.a] Student name should be %s, was %s.\n", name, s1->name);
        release_memory(&reg);
        fail(buf);
    }

    if (strcmp("00000A", s1->id)) {
        sprintf(buf, "[Task 3.4.a] Student ID should be %s, was %s.\n", "00000A", s1->id);
        release_memory(&reg);
        fail(buf);
    }

    if (s1->age != 20) {
        sprintf(buf, "[Task 3.4.a] Student age should be 20, was %d\n.", s1->age);
        release_memory(&reg);
        fail(buf);
    }

    if (strcmp("ELEC-A1100", s1->course)) {
        sprintf(buf, "[Task 3.4.a] Course code not should be %s, was %s.\n", "ELEC-A1100", s1->course);
        release_memory(&reg);
        fail(buf);
    }

    if (s1->points != NULL) {
        sprintf(buf, "[Task 3.4.a] Points array should be NULL, was %p.\n", s1->points);
        release_memory(&reg);
        fail(buf);
    }

    if (s1->numPoints != 0) {
        sprintf(buf, "[Task 3.4.a] numPoints should be 0, was %d.\n", s1->numPoints);
        release_memory(&reg);
        fail(buf);
    }

    //free(name);
    //fail_unless(!strcmp("Teemu Teekkari", s1->name), "[Task 17.1] Student name was not allocated from heap.");

    if (reg.count != 1) {
        sprintf(buf, "[Task 3.4.a] After adding a student, student count should be 1, was %d.\n",
                reg.count);
        release_memory(&reg);
        fail(buf);
    }

    if (reg.array != s1) {
        release_memory(&reg);
        fail("[Task 3.4.a] After adding one student, the returned value does not point to the beginning of array.\n");
    }

    Student *s2 = create_student(&reg, "Peppilotta Sikuriina Rullakartiina Kissanminttu Efraimintytar Pitkatossu", "12345B", 10, "ELEC-A1100");
    if ((reg.array) + 1 != s2) {
        release_memory(&reg);
        fail("[Task 3.4.a] After adding second student, the returned value does not point to the second array member.\n");
    }

    if (reg.count != 2) {
        sprintf(buf, "[Task 3.4.a] After adding second student, the student count should be 2, was %d.\n",
                reg.count);
        release_memory(&reg);
        fail(buf);
    }

#if 0
    Student *s3 = create_student(&reg, "Ylimaaraisia Merkkeja", "99999Ffoofoofoofoo", 60, "ELEC-A1111-even-16-characters-is-too-much-for-a-course-code");
    assert(s3 != NULL);

    if (strcmp("99999Ff", s3->id)) {
        sprintf("[Task 3.4.a] Too long student id truncated incorrectly: %s, should be %s\n",
                s3->id, "99999Ff");
        release_memory(&reg);
        fail(buf);
    }
    if (strcmp("ELEC-A1111-even", s3->course)) {
        sprintf(buf, "[Task 3.4.a] Too long course code truncated incorrectly: %s, should be %s\n",
                s3->course, "ELEC-A1111-even");
        release_memory(&reg);
        fail(buf);
    }
#endif
    release_memory(&reg);
}

END_TEST

Students *initialize_reg(Students *reg) {
    //Students *reg = malloc(sizeof(Students));
    assert(reg != NULL);
    reg->count = 0;
    reg->array = NULL;
    create_student(reg, "Teemu Teekkari", "00000A", 20, "ELEC-A1100");
    create_student(reg, "Matti Meikäläinen", "12345B", 28, "ELEC-A1100");
    create_student(reg, "Wow", "33333C", 28, "ELEC-A1100");
    create_student(reg, "Much Student", "98765H", 28, "ELEC-A1100");
    create_student(reg, "Such course", "12121R", 28, "ELEC-A1111");
    create_student(reg, "Amaze", "11111T", 28, "ELEC-A1111");
    return reg;
}

START_TEST(test_find_student) {
    Students regb;
    char buf[160];
    Students *reg = initialize_reg(&regb);
    Student *sf3 = find_student(reg, "33333C", "ELEC-A1100");
    Student *sf6 = find_student(reg, "11111T", "ELEC-A1111");

    if (sf3 == NULL) {
        release_memory(reg);
        fail("[Task 3.4.b] find_student returned NULL for existing student ID %s.\n", "33333C");
    }

    if (strcmp(sf3->id, "33333C")) {
        sprintf(buf, "[Task 3.4.b] find_student returned student with wrong id. Searched for: %s, returned: %s", "33333C", sf3->id);
        release_memory(reg);
        fail(buf);
    }

    if (sf6 == NULL) {
        release_memory(reg);
        fail("[Task 3.4.b] find_student returned NULL for existing student %s.\n", "11111T");
    }

    if (strcmp(sf6->id, "11111T")) {
        sprintf(buf, "[Task 3.4.b] find_student returned student with wrong id. Searched for: %s, returned: %s", "11111T", sf6->id);
        release_memory(reg);
        fail(buf);
    }

    if (NULL != find_student(reg, "98989D", "ELEC-A1112")) {
        release_memory(reg);
        fail("[Task 3.4.b] find_student should return NULL for nonexistent students.\n");
    }

    /*    fail_unless(NULL == find_student(reg, "98989D", "ELEC-A1100"), "[Task 17.2] find_student should return NULL for nonexistent students.");
        fail_unless(NULL == find_student(reg, "33333C", "ELEC-A1112"), "[Task 17.2] find_student should return NULL for nonexistent students.");
        fail_unless(NULL == find_student(reg, "33333C", "ELEC-A1111"), "[Task 17.2] find_student should return NULL for nonexistent students.");*/
    release_memory(reg);
}

END_TEST


START_TEST(test_delete_student) {
    char buf[160];
    Students regb;
    Students *reg = initialize_reg(&regb);
    if (reg->count != 6) {
        sprintf(buf, "[Task 3.4.c] Wrong student count after adding 6 students, you have %d\n.",
                reg->count);
        release_memory(reg);
        fail(buf);
    }

    if (!delete_student(reg, "11111T", "ELEC-A1111")) {
        sprintf(buf, "[Task 3.4.c] delete_student() failed for existing student 11111T.\n");
        release_memory(reg);
        fail(buf);
    }

    if (reg->count != 5) {
        sprintf(buf, "[Task 3.4.c] After deleting one student, student count should be 5, you had %d.\n",
                reg->count);
        release_memory(reg);
        fail(buf);
    }

    if (!delete_student(reg, "33333C", "ELEC-A1100")) {
        sprintf(buf, "[Task 3.4.c] delete_student() failed for existing student 33333C.\n");
        release_memory(reg);
        fail(buf);
    }
    //fail_unless(reg->count == 4, "[Task 17.3] Wrong student count after deletion.");

    assert((reg->array + 2) != NULL);

    if (strcmp((reg->array + 2)->id, "98765H")) {
        sprintf(buf, "[Task 3.4.c] After deleting student 33333C, student %s should be in 3rd array position. You have %s.\n", "98765H", (reg->array + 2)->id);
        release_memory(reg);
        fail(buf);
    }

    if (delete_student(reg, "33330C", "ELEC-A1101")) {
        release_memory(reg);
        fail("[Task 3.4.c] delete_student() should have failed for nonexisting student 33330C.\n");
    }
    /*fail_unless(delete_student(reg, "00000A", "ELEC-A1111") == 0, "[Task 17.3] delete_student() should have failed for nonexisting student.");
    fail_unless(delete_student(reg, "12121R", "ELEC-A1100") == 0, "[Task 17.3] delete_student() should have failed for nonexisting student.");
    fail_unless(delete_student(reg, "00000A", "ELEC-A1100"), "[Task 17.3] delete_student() failed for existing student 00000A.");
    fail_unless(delete_student(reg, "12345B", "ELEC-A1100"), "[Task 17.3] delete_student() failed for existing student 12345B.");
    fail_unless(delete_student(reg, "98765H", "ELEC-A1100"), "[Task 17.3] delete_student() failed for existing student 98765H.");
    fail_unless(delete_student(reg, "12121R", "ELEC-A1111"), "[Task 17.3] delete_student() failed for existing student 12121R.");

    fail_unless(reg->count == 0, "[Task 17.3] Course register should be empty after deleting all students.");*/

    release_memory(reg);
}

END_TEST


void pr_array(char *buf, float *arr, int n) {
    char b[40];
    sprintf(buf, "{");
    while (n--) {
        sprintf(b, "%.1f", *arr++);
        if (n)
            strcat(b, ", ");
        strcat(buf, b);
    }
    strcat(buf, "}");
}

START_TEST(test_set_points) {
    Students regb;
    Students *reg = initialize_reg(&regb);
    char arrbuf[80];
    char buf[160];
    float p[4];
    int i;
    for (i = 0; i < 4; i++) {
        p[i] = (float)(rand() % 10) / 2;
    }
    pr_array(arrbuf, p, 4);

    if (!set_points(reg, "00000A", "ELEC-A1100", p, 4)) {
        sprintf(buf, "[Task 3.4.d] set_points() returned 0 for student 00000A with array %s, but it should have succeeded.\n",
                arrbuf);
        release_memory(reg);
        fail(buf);
    }
    Student *st = &(reg->array[0]);

    if (st->points == NULL) {
        sprintf(buf, "[Task 3.4.d] Points array not created for array %s (is still NULL).\n",
                arrbuf);
        release_memory(reg);
        fail(buf);
    }

    char arr2[80];
    pr_array(arr2, st->points, 4);
    for (i = 0; i < 4; i++) {
        if (st->points[i] != p[i]) {
            sprintf(buf, "[Task 3.4.d] Point array differs. Should be %s. You have %s\n",
                    arrbuf, arr2);
            release_memory(reg);
            fail(buf);
        }
    }
    /*float q[] = {2, 5, 1, 6, 12, 1};
    fail_unless(set_points(reg, "00000A", "ELEC-A1100", q, 6) == 1, "[Task 17.4] set_points() did not return 1 on success or failed when it was not supposed to");
    fail_unless(st->points != NULL, "[Task 17.4] Points array for student not created");
    fail_unless(st->points[4] == 12, "[Task 17.4] Setting points failed on student");
    fail_unless(set_points(reg, "00000A", "ELEC-A1111", p, 3) == 0, "[Task 17.4] set_points() did not return 0 on failure");*/

    release_memory(reg);
}

END_TEST


int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-3.4");

    /* TODO: define tests */
    tmc_register_test(s, test_create_student, "3.4.a");
    tmc_register_test(s, test_find_student, "3.4.b");
    tmc_register_test(s, test_delete_student, "3.4.c");
    tmc_register_test(s, test_set_points, "3.4.d");

    return tmc_run_tests(argc, argv, s);
}
