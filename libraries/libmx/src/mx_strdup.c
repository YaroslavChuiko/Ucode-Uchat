#include "../inc/libmx.h"

char *mx_strdup(const char *s1)
{
    char *dup = mx_strnew(mx_strlen(s1));

    if (dup == NULL)
    {
        return NULL;
    }

    dup = mx_strcpy(dup, s1);

    return dup;
}
