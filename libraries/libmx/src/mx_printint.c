#include "../inc/libmx.h"

void mx_printint(int n)
{
    int num = n;

    if (n == -2147483648)
    {
        char str[] = "-2147483648";
        
        for (int i = 0; str[i] != '\0'; i++)
        {
            mx_printchar(str[i]);
        }
        return;
    }

    if (n < 0)
    {
        num = n * -1;
        mx_printchar('-');
    }

    if (num >= 10)
    {
        mx_printint(num / 10);
    }

    mx_printchar((num % 10) + 48);
}
