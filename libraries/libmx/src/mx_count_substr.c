#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub)
{
    if (str == NULL)
    {
        return -1;
    }
    
    int result = 0;

    if (mx_strlen(sub) == 0)
    {
        return 0;
    }

    while ((str = mx_strstr(str, sub)))
    {
        str++;
        result++;
    }

    return result;
}
