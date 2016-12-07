#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/address.h"

void release(struct addrRecord *rec)
{
    struct addrRecord *temp;  
    while (rec) {
        temp = rec;
        rec = rec->next;
        free(temp);
    }
}


struct addrRecord *initRec(const char *names[], const unsigned char* addrs[],
        const adType types[], int n, char *outbuf)
{
    struct addrRecord *first = NULL;
    struct addrRecord *nrec;
    int i;
    for (i = 0; i < n; i++) {
        if (types[i] == IPv4) {
            addr_4 a4;
            memcpy(a4.a, addrs[i], 4);
            nrec = storeIPv4(first, names[i], &a4);
            if (!nrec) {
                sprintf(outbuf, "Storing IPv4 address with name %s failed. StoreIPv4 returned NULL.",
                        names[i]);
                release(first);
                return NULL;
            }
        } else if (types[i] == IPv6) {
            addr_6 a6;
            memcpy(a6.a, addrs[i], 16);
            nrec = storeIPv6(first, names[i], &a6);
            if (!nrec) {
                sprintf(outbuf, "Storing IPv6 address with name %s failed. StoreIPv6 returned NULL.",
                        names[i]);
                release(first);
                return NULL;
            }            
        } else if (types[i] == UNIX) {
            addr_un au;
            strncpy(au.a, (char *)addrs[i], 108);
            nrec = storeUnix(first, names[i], &au);
            if (!nrec) {
                sprintf(outbuf, "Storing Unix domain address with name %s failed. StoreUnix returned NULL.",
                        names[i]);
                release(first);
                return NULL;
            }
        } else {
            return NULL;
        }
        first = nrec;
    }
    return first;
}

void sprintIPv4(char *buf, const unsigned char *ad) {
	sprintf(buf, "%d.%d.%d.%d", ad[0], ad[1], ad[2], ad[3]);
}

void sprintIPv6(char *buf, const unsigned char *ad) {
	int i;
        char tb[8];
        buf[0] = 0;
	for (i = 0; i < 16; i++) {
		if (!(i % 2) && i)
			strcat(buf, ":");
		sprintf(tb, "%02x", ad[i]);
                strcat(buf,tb);
	}
}

void sprintUnix(char *buf, const char *ad) {
	sprintf(buf, "%s", ad);
}

START_TEST(test_store)
{
    char outbuf[120];
    char out2[120];
    struct addrRecord *first;
    int n = 3;
    const char *names[] = {"www.example.com", "src.aalto.fi", "unix.domain.socket"};
    const unsigned char *addrs[] = {(unsigned char *)"abcd",
				    (unsigned char *)"defgdefgdefgdefg",
				    (unsigned char *)"/some/fairly/long/unix/address"};
    const adType types[] = {IPv4, IPv6, UNIX};
    
    first = initRec(names, addrs, types, n, outbuf);
    if (!first) {
        fail("[Task 4.1.a] %s", outbuf);
    }
    struct addrRecord *next = first;

    int i;
    for (i = n -1; i >= 0; i--) {
        if (next->type != types[i]) {
            adType t = next->type;
            release(first);
            fail("[Task 4.1.a] Wrong type for name %s. you have %d, should be %d",
                    names[i], t, types[i]);
        }
        if (strcmp(next->name, names[i])) {
            sprintf(outbuf, "[Task 4.1.a] Wrong name in linked list. you have: '%s', should be '%s'",
                    next->name, names[i]);
            release(first);
            fail("%s", outbuf);
        }
        if (next->type == IPv4) {
            if (memcmp(next->u.in4.a, addrs[i], 4)) {
                sprintIPv4(outbuf, next->u.in4.a);
                sprintIPv4(out2, addrs[i]);
                release(first);
                fail("[Task 4.1.a] Wrong IPv4 address. You have: '%s'. Should be: '%s'",
                        outbuf, out2);
            }
        }
        if (next->type == IPv6) {
            if (memcmp(next->u.in6.a, addrs[i], 16)) {
                sprintIPv6(outbuf, next->u.in6.a);
                sprintIPv6(out2, addrs[i]);
                release(first);
                fail("[Task 4.1.a] Wrong IPv6 address. You have: '%s'. Should be: '%s'",
                        outbuf, out2);
            }
        }
        if (next->type == UNIX) {
		if (strncmp(next->u.un.a, (char *)addrs[i], 108)) {
                sprintUnix(outbuf, next->u.un.a);
                sprintUnix(out2, (char *)addrs[i]);
                release(first);
                fail("[Task 4.1.a] Wrong Unix domain address. You have: '%s'. Should be: '%s'",
                        outbuf, out2);
            }
        }
        next = next->next;
    }
    release(first);
}
END_TEST


START_TEST(test_query)
{
    struct addrRecord *first, *q;
    char outbuf[120];
    char out2[120];
    int n = 3;
    const char *names[] = {"www.example.com", "src.aalto.fi", "unix.domain.socket"};
    const unsigned char *addrs[] = { (unsigned char *)"abcd",
				     (unsigned char *)"defgdefgdefgdefg",
				     (unsigned char *)"/some/fairly/long/unix/address"};
    const adType types[] = {IPv4, IPv6, UNIX};
    
    first = initRec(names, addrs, types, n, outbuf);
    if (!first) {
        fail("[Task 4.1.b] Initializing linked list failed. Are Store functions implemented properly?");
    }

    int i;
    for (i = 0; i < n; i++) {
        q = findAddress(first, names[i]);
        if (!q) {
            release(first);
            fail("[Task 4.1.b] Did not find name '%s' that was earlier added to the list",
                    names[i]);
        }
        if (strncmp(q->name, names[i], 20)) {
            sprintf(outbuf, "[Task 4.1.b] findAddress returned wrong name: '%s' when searching for '%s'",
                    q->name, names[i]);
            release(first);
            fail("%s", outbuf);
        }
        if (q->type != types[i]) {
            adType t = q->type;
            release(first);
            fail("[Task 4.1.b] findAddress returned wrong type when searching name '%s': %d. Should be %d",
                    names[i], t, types[i]);
        }
        if (q->type == IPv4) {
            if (memcmp(q->u.in4.a, addrs[i], 4)) {
                sprintIPv4(outbuf, q->u.in4.a);
                sprintIPv4(out2, addrs[i]);
                release(first);
                fail("[Task 4.1.b] findAddress returned wrong IPv4 address. You have: '%s'. Should be: '%s'",
                        outbuf, out2);
            }            
        }
        if (q->type == IPv6) {
            if (memcmp(q->u.in6.a, addrs[i], 16)) {
                sprintIPv6(outbuf, q->u.in6.a);
                sprintIPv6(out2, addrs[i]);
                release(first);
                fail("[Task 4.1.b] findAddress returned wrong IPv6 address. You have: '%s'. Should be: '%s'",
                        outbuf, out2);
            }            
        }
        if (q->type == UNIX) {
		if (strncmp(q->u.un.a, (char *)addrs[i], 108)) {
                sprintUnix(outbuf, q->u.un.a);
                sprintUnix(out2, (char *)addrs[i]);
                release(first);
                fail("[Task 4.1.b] findAddress returned wrong Unix domain address. You have: '%s'. Should be: '%s'",
                        outbuf, out2);
            }            
        }
    }
    release(first);
}
END_TEST

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
        if (*student == '\n') line++;
        student++; model++; i++;
    }
    if (*model) {
        sprintf(infostr, "output correct until position: %d, but shorter than expected\n",
                i);
        return -1;
    }
    return 0;
}

void printIPv4s(addr_4 *ad) {
    printf("%d.%d.%d.%d", ad->a[0], ad->a[1], ad->a[2], ad->a[3]);
}

void printIPv6s(addr_6 *ad) {
    int i;
    for (i = 0; i < 16; i++) {
        if (!(i % 2) && i)
            printf(":");
        printf("%02x", ad->a[i]);
    }
}

void printUnixs(addr_un *ad) {
    printf("%s", ad->a);
}

START_TEST(test_print)
{
    char student[1024];
    char model[1024];
    char infostr[1024];
    char outbuf[300];
    struct addrRecord *first, *q;
    int n = 3;

    student[0] = 0;

    const char *names[] = {"www.example.com", "src.aalto.fi", "unix.domain.socket"};
    const unsigned char *addrs[] = { (unsigned char *)"abcd",
				     (unsigned char *)"defgdefgdefgdefg",
				     (unsigned char *)"/some/fairly/long/unix/address"};
    const adType types[] = {IPv4, IPv6, UNIX};
    
    first = initRec(names, addrs, types, n, outbuf);
    if (!first) {
        fail("[Task 4.1.c] Initializing linked list failed. Are Store functions implemented properly?");
    }
    q = first;
    int i;
    for (i = 0; i < n; i++) {
        int l = 0;
        freopen("mockoutput", "w", stdout);
        printAddress(q);
        fflush(stdout);
        FILE *fp = fopen("mockoutput", "r");
        while (fgets(student + l, 1024 - l, fp) != NULL) l = strlen(student);
        fclose(fp);
        freopen("mockoutput", "w", stdout);
        if (q->type == IPv4) printIPv4s(&q->u.in4);
        else if (q->type == IPv6) printIPv6s(&q->u.in6);
        else if (q->type == UNIX) printUnixs(&q->u.un);
        fflush(stdout);
        fp = fopen("mockoutput", "r");
        l = 0;
        while (fgets(model + l, 1024 - l, fp) != NULL) l = strlen(model);
        fclose(fp);

        if (mycompare(student, model, infostr)) {
           snprintf(outbuf, 300, "Your output: '%s'\nReference output: '%s'\n", student, model);
           release(first);
           fail("[Task 4.1.c] Incorrect output\n.%s Reason: %s", outbuf, infostr);
       }
        q = q->next;
    }
    release(first);
}
END_TEST


int main(int argc, const char *argv[])
{
    	Suite *s = suite_create("Test-4.1");

        /* TODO: define tests */
	tmc_register_test(s, test_store, "4.1.a");
	tmc_register_test(s, test_query, "4.1.b");
	tmc_register_test(s, test_print, "4.1.c");
        
	return tmc_run_tests(argc, argv, s);
}
