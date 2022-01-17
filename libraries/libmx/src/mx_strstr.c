#include "../inc/libmx.h"

char *mx_strstr(const char *s1, const char *s2)
{
    if (!mx_strlen(s2))
    {
        return (char *)s1;
    }

    while (*s1)
    {
        char *p = mx_strchr(s1, s2[0]);

        if ((*s1 == *s2) && mx_strncmp(p, s2, mx_strlen(s2)) == 0)
        {
            return (char *)&(p[0]);
        }
        s1++;
    }
    
    return NULL;
}
