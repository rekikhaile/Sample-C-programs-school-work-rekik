#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/minesweeper.h"

int mycompare(char *student, char *model, char *infostr)
{
    int i = 0, line = 1;
    while(*student) {
        if (!(*model)) {
            sprintf(infostr, "your output is longer than expected: character: '%c', position: %d, line: %d\n",
                    *student, i, line);
            return -1;
        }
        if (*student != *model) {
            sprintf(infostr, "position: %d, line: %d, your output: '%c' , expected: '%c'\n", 
                    i, line, *student, *model);
            return -1;
        }
        if (*student == '\n') {
            line++;
            i = -1;
        }
        student++; model++; i++;
    }
    if (*model) {
        sprintf(infostr, "output correct until position: %d, but shorter than expected\n",
                i);
        return -1;
    }
    return 0;
}

void free_resources(Field *f)
{
    unsigned int i;
    for (i = 0; i < f->ysize; i++) {
        free((f->places)[i]);
    }
    free(f->places);
    free(f);
}

Field *init_static(void)
{
    unsigned int i, j;
    unsigned int form[] =   {1, 0, 1, 0, 0,
                             0, 1, 1, 0, 0,
                             1, 1, 1, 0, 0,
                             0, 0, 0, 0, 0,
                             0, 1, 0, 1, 0};
    Field *f = createField(5, 5);
    for (j = 0; j < f->ysize; j++){
        for (i = 0; i < f->xsize; i++) {
            (f->places)[j][i] = form[j*5 + i] == 0 ? UNKNOWN_FREE : UNKNOWN_MINE;
        }
    }
    return f;

}

START_TEST(test_createField)
{
    unsigned int i, j, k, xs, ys;
    Field *f;
    for (i = 0; i < 3; i++) {
        xs = 10 + (rand() % 90);
        ys = 10 + (rand() % 90);
        f = createField(xs, ys);
        if (!f) {
            fail("[4.2.a] createField returned NULL");
        }
        if (f->xsize != xs || f->ysize != ys) {
            free_resources(f);
            fail("[4.2.a] Incorrect dimensions in Field struct for %ux%u field.", ys, xs);
        }
        for (j = 0; j < ys; j++) {
            for (k = 0; k < xs; k++) {
                if ((f->places)[j][k] != UNKNOWN_FREE) {
                    free_resources(f);
                    fail("[4.2.a] Place (%u, %u) initialized incorrectly.", j, k);
                }
            }
        }
        free_resources(f);
    } 
}
END_TEST


START_TEST(test_checkPlace)
{
    unsigned int i, j, k, xs, ys, m;
    State prev;
    Field *f;
    for (i = 0; i < 3; i++) {
        xs = 10 + (rand() % 90);
        ys = 10 + (rand() % 90);
        m = xs*ys/5;
        f = createField(xs, ys);
        if (!f) {
            fail("[4.2.b] Implement createField first");
        }
        deployMines(f, m);
        int ret;
        int xi = -(rand() % 100);
        int yi = -(rand() % 100);
        if ((ret = checkPlace(f, xi, yi)) != -1) {
            free_resources(f);
            fail("[4.2.b] checkPlace should return -1 for out-of-bounds indices (%d,%d). You returned %d.\n",
                    xi, yi, ret);
        }
        xi = xs + (rand() % 100);
        yi = ys + (rand() % 100);
        if ((ret = checkPlace(f, xi, yi)) != -1) {
            free_resources(f);
            fail("[4.2.b] checkPlace should return -1 for out-of-bounds indices (%d,%d). You returned %d.\n",
                    xi, yi, ret);
        }       
        
        for (j = 0; j < ys; j++) {
            for (k = 0; k < xs; k++) {
                prev = (f->places)[j][k];
                ret = checkPlace(f, k, j);
                if (prev == UNKNOWN_FREE) {
                    if (ret != 0) {
                        free_resources(f);
                        fail("[4.2.b] checkPlace should return 0 for free positions. You returned %d.\n",
                                ret);
                    }
                    if ((f->places)[j][k] != KNOWN_FREE) {
                        free_resources(f);
                        fail("[4.2.b] checkPlace should change visited unknown position to known");
                    }
                } else if (prev == UNKNOWN_MINE) {
                    if (ret != 1) {
                        free_resources(f);
                        fail("[4.2.b] checkPlace should return 1 for mined positions. You returned %d.\n",
                                ret);
                    }
                    if ((f->places)[j][k] != KNOWN_MINE) {
                        free_resources(f);
                        fail("[4.2.b] checkPlace should change visited unknown position to known");
                    }
                } else {
                    free_resources(f);
                    fail("[4.2.b] Field is initialized incorrectly");
                }
                if (ret != -1 && ret != 0 && ret != 1) {
                    free_resources(f);
                    fail("[4.2.b] checkPlace returned %d. Valid return values are -1, 0 and 1.\n",
                            ret);
                }
            }
        }

        free_resources(f);
    }    
}
END_TEST


START_TEST(test_countNeighbours)
{
    unsigned int i, j, ans, corr;

    
    unsigned int sol[] =    {1, 4, 2, 2, 0,
                             4, 6, 4, 3, 0,
                             2, 4, 3, 2, 0,
                             3, 4, 4, 2, 1,
                             1, 0, 2, 0, 1};
    Field *f = init_static();
    if (!f) {
        fail("[4.2.c] Implement createField first");
    }
    for (j = 0; j < 5; j++) {
       for (i = 0; i < 5; i++) {
            ans = countNeighbours(f, i, j);
            corr = sol[j*5 + i];
            if (ans != corr) {
                free_resources(f);
                fail("[4.2.c] countNeighbours returned %u for position (%u, %u). Should have returned %u.", ans, j, i, corr);
            }
        }
    }
    free_resources(f);
}
END_TEST



START_TEST(test_printField)
{
    char infostr[100];
    char rightstr[] = "? ? * ? ? \n? ? ? ? . \n? ? ? ? ? \n3 ? ? ? ? \n? ? 2 ? ? \n";
    Field *f = init_static();
    if (!f) {
        fail("[4.2.d] Implement createField first");
    }

    checkPlace(f, 2, 0);
    checkPlace(f, 4, 1);
    checkPlace(f, 0, 3);
    checkPlace(f, 2, 4);
//    for (int i = 0; i < 25; i++) {
//        checkPlace(f, i/5, i % 5);
//    }
    freopen("mockoutput", "w", stdout);
    printField(f);
    fflush(stdout);
    FILE *fp = fopen("mockoutput", "r"); 
    char str [300]; 
    int n = fread(str, 1, sizeof(str), fp); 
    str[n] = 0; 
    fclose(fp);
 //   fprintf(stderr, "%s\n----\n", str);
    int res = mycompare(str, rightstr, infostr);
    if (res) {
        free_resources(f);
        fail("[4.2.d] Your output:\n%s\nReference output:\n%s\nReason: %s\n",
                str, rightstr, infostr);
    }
    free_resources(f);

}
END_TEST


int main(int argc, const char *argv[])
{
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-4.2");

        /* TODO: define tests */
    tmc_register_test(s, test_createField, "4.2.a");
    tmc_register_test(s, test_checkPlace, "4.2.b");
    tmc_register_test(s, test_countNeighbours, "4.2.c");
    tmc_register_test(s, test_printField, "4.2.d");
        
    return tmc_run_tests(argc, argv, s);
}
