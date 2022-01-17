#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n)
{
    size_t len = n > (size_t)mx_strlen(s1) ? (size_t)mx_strlen(s1) : n;

    char *dup = mx_strnew(len);

    if (dup == NULL)
    {
        return NULL;
    }

    dup = mx_strncpy(dup, s1, len);

    return dup;
}
