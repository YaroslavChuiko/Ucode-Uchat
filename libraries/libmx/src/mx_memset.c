#include "../inc/libmx.h"

void *mx_memset(void *b, int c, size_t len)
{
    unsigned char *p = (unsigned char *)b;
    
    while (len--)
    {
        *p = (unsigned char)c;
        p++;
    }
    
    return b;
}
