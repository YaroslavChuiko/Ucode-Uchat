#include "../inc/libmx.h"

int mx_atoi(const char *str)
{
    if (str == NULL) return 0;
    int result = 0;
    int sign = 1;
    int i = 0;

    while (mx_isspace(str[i]))
    {
        i++;
    }

    if (str[i] == '-' || str[i] == '+')
    {
        sign = 1 - 2 * (str[i++] == '-');
    }

    while (mx_isdigit(str[i]))
    {
        result = result * 10 + (str[i++] - 48);
    }

    return result * sign;
}
