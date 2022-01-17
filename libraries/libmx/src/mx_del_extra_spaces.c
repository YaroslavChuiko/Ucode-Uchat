#include "../inc/libmx.h"

char *mx_del_extra_spaces(const char *str)
{
    if (str == NULL)
    {
        return NULL;
    }
    
    char *tmp = mx_strtrim(str);

    int x = 0;
    for (int i = 0; tmp[i] != '\0'; i++)
    {
        if (!mx_isspace(tmp[i]))
        {
            tmp[x++] = tmp[i];
        }
        if ((!mx_isspace(tmp[i])) && mx_isspace(tmp[i + 1]))
        {
            tmp[x++] = ' ';
        }
    }
    tmp[x] = '\0';
    return tmp;
}
