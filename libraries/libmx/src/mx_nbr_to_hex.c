#include "../inc/libmx.h"

char *mx_nbr_to_hex(unsigned long nbr)
{
    if ((long)nbr < 0)
    {
        return 0;
    }

    if (nbr == 0)
    {
        return "0\0";
    }

    char hexaDeciNum[100];
    int i = 0;
    while (nbr != 0)
    {
        int temp = 0;
        temp = nbr % 16;

        if (temp < 10)
        {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else
        {
            hexaDeciNum[i] = temp + 87;
            i++;
        }
        nbr = nbr / 16;
    }
    char *result = mx_strnew(i);

    for (int j = i - 1, k = 0; j >= 0; j--, k++)
    {
        result[k] = hexaDeciNum[j];
    }

    return result;
}
