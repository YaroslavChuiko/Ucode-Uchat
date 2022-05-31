#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n)
{
    if (s == NULL)
    {
        return NULL;
    }
    
    unsigned char *str = (unsigned char *)s;

    while (n--)
    {
        if (*str == (unsigned char)c)
        {
            return str;
        }
        str++;
    }
    
    return NULL;
}
