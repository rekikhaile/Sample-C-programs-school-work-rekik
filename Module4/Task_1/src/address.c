#include <stdio.h>
#include "address.h"

/* Print an IPv4 address to standard output */
void printIPv4(addr_4 *ad) {
	printf("%d.%d.%d.%d", ad->a[0], ad->a[1], ad->a[2], ad->a[3]);
}

/* Print an IPv6 address to standard output */
void printIPv6(addr_6 *ad) {
	int i;
	for (i = 0; i < 16; i++) {
		if (!(i % 2) && i)
			printf(":");
		printf("%02x", ad->a[i]);
	}
}

/* Print an Unix domain address to standard output */
void printUnix(addr_un *ad) {
	printf("%s", ad->a);
}


/* Print given address to standard output, following the right format 
 * depending on the type of the address. */
void printAddress(struct addrRecord *ad)
{
}


/* Find address record based on given name
 * 
 * Parameters:
 * first: pointer to the beginning of the linked list
 * name: the name to be found in the linked list
 * 
 * Returns:
 * Address record with matching name */
struct addrRecord *findAddress(struct addrRecord *first, const char *name) {
return NULL;   // replace this
}


/* Stores a new address record to the linked list
 * 
 * Parameters:
 * first: pointer to the start of the linked list
 * name: name of the new record to be added (same name can be stored multiple times)
 * ad: IPv4 address to be stored with the name
 * 
 * Returns:
 * Pointer to the new node in linked list (that becomes the first node in list) */
struct addrRecord *storeIPv4(struct addrRecord *first, const char *name, const addr_4 *ad)
{
return NULL;   // replace this
}


/* Stores a new address record to the linked list
 * 
 * Parameters:
 * first: pointer to the start of the linked list
 * name: name of the new record to be added (same name can be stored multiple times)
 * ad: IPv6 address to be stored with the name
 * 
 * Returns:
 * Pointer to the new node in linked list (that becomes the first node in list) */
struct addrRecord *storeIPv6(struct addrRecord *first, const char *name, const addr_6 *ad)
{
return NULL;   // replace this
}


/* Stores a new address record to the linked list
 * 
 * Parameters:
 * first: pointer to the start of the linked list
 * name: name of the new record to be added (same name can be stored multiple times)
 * ad: Unix domain address to be stored with the name
 * 
 * Returns:
 * Pointer to the new node in linked list (that becomes the first node in list) */
struct addrRecord *storeUnix(struct addrRecord *first, const char *name, const addr_un *ad)
{
return NULL;   // replace this
}
