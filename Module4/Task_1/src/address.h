#ifndef AALTO_ADDRESS_H
#define	AALTO_ADDRESS_H

/* container for 32-bit IPv4 address */
typedef struct {
	unsigned char a[4];
} addr_4;

/* container for 128-bit IPv6 address */
typedef struct {
	unsigned char a[16];
} addr_6;

/* container for Unix domain address */
typedef struct {
	char a[108];
} addr_un;

typedef enum {
	NONE, // address not in use
	IPv4,
	IPv6,
	UNIX
} adType;

/* One node in linked list of name / address entries */
struct addrRecord {
	char name[20];
	adType type;
	union {
		addr_4 in4;
		addr_6 in6;
		addr_un un;
	} u;
        struct addrRecord *next;
};

/* Store IPv4 address to addrRecord */
struct addrRecord *storeIPv4(struct addrRecord *first, const char *name, const addr_4 *ad);

/* Store IPv6 address to addrRecord */
struct addrRecord *storeIPv6(struct addrRecord *first, const char *name, const addr_6 *ad);

/* Store Unix domain address to addrRecord */
struct addrRecord *storeUnix(struct addrRecord *first, const char *name, const addr_un *ad);

/* Find address from linked list starting from 'first' */
struct addrRecord *findAddress(struct addrRecord *first, const char *name);

/* Prints the address in address record to standard output */
void printAddress(struct addrRecord *ad);

#endif	/* AALTO_ADDRESS_H */
