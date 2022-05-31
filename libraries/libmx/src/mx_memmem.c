#include "../inc/libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len)
{
    if (!big_len || !little_len || little_len > big_len || !big || !little)
    {
        return NULL;
    }

    unsigned char *b = (unsigned char *)big;
    unsigned char *l = (unsigned char *)little;

    while (big_len >= little_len)
    {
        if (!mx_memcmp(b, l, little_len))
        {
            return b;
        }
        b++;
        big_len--;
    }

    return NULL;
}
