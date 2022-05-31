#include <stddef.h>

char *mx_strchr(const char *s, int c)
{
    int length;
    for (length = 0; s[length] != '\0'; length++)

        for (int i = 0; i < length + 1; i++)
        {
            if (s[i] == c)
            {
                return (char *)&(s[i]);
            }
        }
    return NULL;
}
