#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n)
{
    if (s == NULL)
    {
        return NULL;
    }

    unsigned char *str = (unsigned char *)s;

    str += mx_strlen(s);

    while (n--)
    {
        if (*str == (unsigned char)c)
        {
            return str;
        }
        str--;
    }

    return NULL;
}
