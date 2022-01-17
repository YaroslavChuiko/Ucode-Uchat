#include "../inc/libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n)
{
    unsigned char *csrc = (unsigned char *)src;
    unsigned char *cdst = (unsigned char *)dst;

    for (size_t i = 0; i < n; i++)
    {
        if (csrc[i] == (unsigned char)c)
        {
            cdst[i] = csrc[i];

            // return (void *)&(((unsigned char *)dst)[i + 1]); //???
            return (void *)&(cdst[i + 1]);                   //???
        }

        cdst[i] = csrc[i];
    }

    return NULL;
}
