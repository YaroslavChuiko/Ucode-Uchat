#include "../inc/libmx.h"

int mx_digit_count(int number)
{
    int counter = 0;

    do
    {
        number /= 10;
        ++counter;
    } while (number != 0);

    return counter;
}

char *mx_itoa(int number)
{
    if (number == -2147483648) {
        return mx_strdup("-2147483648");
    }

    char *result = mx_strnew(mx_digit_count(number));
    int sign;
    
    if ((sign = number) < 0)
    {
        number = -number;
    }

    int i = 0;
    do {
        result[i++] = number % 10 + 48; 
    
    } while ((number /= 10) > 0);
    
    if (sign < 0)
    {
        result[i++] = '-';
    }
    
    result[i] = '\0';

    mx_str_reverse(result);
    
    return result;
}
