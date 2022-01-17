#include "../inc/libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2)
{
    int s1Length = mx_strlen(s1);
    int s2Length = mx_strlen(s2);

    for (int i = s1Length, j = 0; j < s2Length + 1; i++, j++)
    {
        s1[i] = s2[j];
    }

    return s1;
}
