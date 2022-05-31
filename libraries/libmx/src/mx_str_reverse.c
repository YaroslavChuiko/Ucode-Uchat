#include "../inc/libmx.h"

void mx_str_reverse(char *s)
{
    int length = mx_strlen(s);

    for (int i = 0, j = length - 1; i < length / 2; i++, j--)
    {
        mx_swap_char(&s[i], &s[j]);
    }
}
