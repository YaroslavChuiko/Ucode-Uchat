#include "../inc/libmx.h"

bool mx_isspace(char c)
{
    if (c == '\n' || c == '\t' || c == '\v' || c == '\r' || c == '\f' || c == ' ')
    {
        return true;
    }

    return false;
}
