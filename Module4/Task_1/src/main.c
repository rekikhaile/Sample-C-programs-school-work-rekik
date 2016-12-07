#include <stdio.h>
#include <stdlib.h>
#include "address.h"

int main()
{
    /* Feel free to modify this function to test different things */
    /* For example, you can temporarily hide unimplemented functions
     * inside comments */
    
    struct addrRecord *recs = NULL;
    addr_4 ad4 = {{128, 214, 4, 64}};
    addr_6 ad6 = {{0x20, 0x02, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}};
    addr_un ad_un = {{"/some/fairly/long/unix/address"}};
    recs = storeIPv4(recs, "www.example.com", &ad4);
    if (!recs)
        return EXIT_FAILURE;
    
    recs = storeIPv6(recs, "src.aalto.fi", &ad6);
    if (!recs)
        return EXIT_FAILURE;
    
    recs = storeUnix(recs, "unix.domain.socket", &ad_un);
    if (!recs)
        return EXIT_FAILURE;
    
    struct addrRecord *ar = findAddress(recs, "src.aalto.fi");
    printAddress(ar);
    
    // Free allocated memory
    while (recs) {
        struct addrRecord *r = recs->next;
        free(recs);
        recs = r;
    }
}
