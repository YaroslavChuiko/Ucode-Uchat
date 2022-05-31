#include "../inc/libmx.h"

int mx_count_words(const char *str, char c)
{
    if (str == NULL)
    {
        return -1;
    }

    int words = 0, counter = 0;
    str++;
    
    while (*str != '\0')
    {
        if (*str == c)
        {
            if (*(str - 1) != c)
            {
                words++;
            }
        }
        str++;
        counter++;
    }
    if (*(str - 1) != c && counter)
    {
        words++;
    }
    return words;
}
