#include "../inc/libmx.h"

char *mx_strrchr(const char *s, int c)
{
    for (int i = mx_strlen(s); i >= 0; i--)
    {
        if (s[i] == c)
        {
            return (char *)&(s[i]);
        }
    }
    return NULL;
}
