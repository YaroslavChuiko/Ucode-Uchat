#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n)
{
    if (s1 == s2 || n == 0)
    {
        return 0;
    }

    unsigned char *f = (unsigned char *)s1;
    unsigned char *s = (unsigned char *)s2;

    for (size_t i = 0; i < n; i++)
    {
        if (f[i] != s[i])
        {
            return f[i] - s[i];
        }
    }

    return 0;
}
