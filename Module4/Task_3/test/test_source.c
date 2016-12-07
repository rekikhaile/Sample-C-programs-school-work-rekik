#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include "../src/cmdline.h"

START_TEST(test_parse_cmdline)
{
	int i;
	char **args = NULL;
    char cmdline[] = "cmdline -s 20 -r -t parameter -p 20 filename";
    char orig_cmd[60];
    strcpy(orig_cmd, cmdline);
    const char *argsol[] = { "cmdline", "-s", "20", "-r", "-t", "parameter", "-p",
        "20", "filename" };
    int count = parse_cmdline(&args, cmdline);
    if (count != 9) {
        free(args);
        fail("[Task 4.3.a] Incorrect argument count returned (%d instead of %d) for string '%s'.\n",
                count, 9, orig_cmd);

    }
    for (i = 0; i < 9; i++) {
        if (strcmp(args[i], argsol[i])) {
            char outbuf[160];
            snprintf(outbuf, 160, "[Task 4.3.a] Incorrect argument at index %d ('%s' instead of '%s') for string '%s'.\n",
                    i, args[i], argsol[i], orig_cmd);
            free(args);
            fail("%s", outbuf);
        }
    }
    free(args);
    args = NULL;
    //char cmdline2[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec sed bibendum sem, sed molestie nulla. Pellentesque dapibus id leo quis malesuada. Mauris ultricies felis purus, ac condimentum mauris auctor at. Duis pharetra enim arcu. Vivamus vel elit sed nunc malesuada posuere non sit amet urna. Ut pulvinar pharetra eleifend. Nullam id orci mollis, euismod tortor at, dapibus nisl. Sed tempor molestie mauris, sit amet faucibus lectus convallis eu. Duis eu purus at sem dapibus vestibulum eu nec mauris. Nullam in volutpat sapien. Curabitur luctus est quis lobortis tristique. Pellentesque convallis felis ut lorem cursus, rutrum viverra ante egestas. Sed sagittis.";
    char cmdline2[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec sed bibendum sem";
    //const char *argsol2[] = {"Lorem", "ipsum", "dolor", "sit", "amet,", "consectetur", "adipiscing", "elit.", "Donec", "sed", "bibendum", "sem,", "sed", "molestie", "nulla.", "Pellentesque", "dapibus", "id", "leo", "quis", "malesuada.", "Mauris", "ultricies", "felis", "purus,", "ac", "condimentum", "mauris", "auctor", "at.", "Duis", "pharetra", "enim", "arcu.", "Vivamus", "vel", "elit", "sed", "nunc", "malesuada", "posuere", "non", "sit", "amet", "urna.", "Ut", "pulvinar", "pharetra", "eleifend.", "Nullam", "id", "orci", "mollis,", "euismod", "tortor", "at,", "dapibus", "nisl.", "Sed", "tempor", "molestie", "mauris,", "sit", "amet", "faucibus", "lectus", "convallis", "eu.", "Duis", "eu", "purus", "at", "sem", "dapibus", "vestibulum", "eu", "nec", "mauris.", "Nullam", "in", "volutpat", "sapien.", "Curabitur", "luctus", "est", "quis", "lobortis", "tristique.", "Pellentesque", "convallis", "felis", "ut", "lorem", "cursus,", "rutrum", "viverra", "ante", "egestas.", "Sed", "sagittis."};
    const char *argsol2[] = {"Lorem", "ipsum", "dolor", "sit", "amet,", "consectetur", "adipiscing", "elit.", "Donec", "sed", "bibendum", "sem" };
    char orig_cmd2[120];
    strcpy(orig_cmd2, cmdline2);
    count = parse_cmdline(&args, cmdline2);
    if (count != 12) {
        free(args);
        fail("[Task 4.3.a] Incorrect argument count returned (%d instead of %d) for string '%s'",
                count, 100, orig_cmd2);        
    }
    for (i = 0; i < 12; i++) {
        if (strcmp(args[i], argsol2[i])){
            char outbuf[160];
            snprintf(outbuf, 160, "[Task 4.3.a] Incorrect argument at index %d ('%s' instead of '%s') for string '%s'",
                   i, args[i], argsol2[i], orig_cmd2);
            free(args);
    	    fail("%s", outbuf);
        }
    }
    free(args);
}
END_TEST

void print_cmdline(char **argv, int argc, char *buf)
{
    buf[0] = 0;
    for (int i = 0; i < argc; i++) {
        strcat(buf, argv[i]);
        if (i < argc-1)
            strcat(buf, " ");
    }
}

START_TEST(test_find_options)
{
	char *arg[] = { "cmdline", "-s", "20", "-r", "-t", "parameter", "-p", "20", "filename" };
	const char opts[] = { 's', 'r', 't', 'p' };
    const char *params[] = { "20", NULL, "parameter", "20"};
    struct command *cmds;
    char buffer[100];
    print_cmdline(arg, 9, buffer);
    cmds = find_options(9, arg);
    if (!cmds) {
        fail("[Task 4.3.b] find_options returned NULL");
    }
    int i;
    for (i = 0; i < 4; i++) {
        if (cmds[i].com != opts[i]) {
            char outbuf[160];
            snprintf(outbuf, 160, "[Task 4.3.b] wrong option char at position %d, expected: %c, you gave: %c. Command line was '%s'",
                    i, opts[i], cmds[i].com, buffer);
            free(cmds);
            fail("%s", outbuf);
        }
        if (cmds[i].param == NULL && params[i] != NULL) {
            char outbuf[160];
            snprintf(outbuf, 160, "[Task 4.3.b] wrong parameter at position %d, expected: '%s', you gave: NULL. Command line was '%s'",
                        i, params[i], buffer);
            free(cmds);
            fail("%s", outbuf);
        } else if (cmds[i].param != NULL && params[i] == NULL) {
            char outbuf[160];
            snprintf(outbuf, 160, "[Task 4.3.b] wrong parameter at position %d, expected: NULL, you gave: '%s'. Command line was '%s'",
                        i, cmds[i].param, buffer);
            free(cmds);
            fail("%s", outbuf);
        } else if (cmds[i].param && params[i] && strcmp(cmds[i].param, params[i])) {
            char outbuf[160];
            snprintf(outbuf, 160, "[Task 4.3.b] wrong parameter at position %d, expected: %s, you gave: %s. Command line was '%s'",
                    i, params[i], cmds[i].param, buffer);
            free(cmds);
            fail("%s", outbuf);
        }
    }
    if (cmds[4].com != 0) {
        free(cmds);
        fail("[Task 4.3.b] The command vector should be terminated with a struct command whose command char is \\0.");
    }
    free(cmds);
}
END_TEST


int main(int argc, const char *argv[])
{
    	Suite *s = suite_create("Test-4.3");

        /* TODO: define tests */
	tmc_register_test(s, test_parse_cmdline, "4.3.a");
	tmc_register_test(s, test_find_options, "4.3.b");
        
	return tmc_run_tests(argc, argv, s);
}
