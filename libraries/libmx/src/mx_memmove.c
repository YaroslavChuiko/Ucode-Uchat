#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len)
{
    unsigned char *tmp = (unsigned char *)malloc(sizeof(unsigned char) * len);

    if (tmp == NULL)
    {
        return NULL;
    }
    
    tmp = mx_memcpy(tmp, src, len);
    dst = mx_memcpy(dst, tmp, len);

    free(tmp);

    return dst;
}
