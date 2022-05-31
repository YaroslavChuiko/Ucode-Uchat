#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace)
{
    if (!str || !sub || !replace)
    {
        return NULL;
    }

    int subs_count = mx_count_substr(str, sub);
    int sub_len = mx_strlen(sub);
    int rep_len = mx_strlen(replace);

    char *result = mx_strnew(mx_strlen(str) + (rep_len - sub_len) * subs_count);
    char *tmp = result;

    while (subs_count--)
    {
        int len_front = mx_get_substr_index(str, sub);
        tmp = mx_strncpy(tmp, str, len_front) + len_front;
        tmp = mx_strcpy(tmp, replace) + rep_len;
        str += len_front + sub_len;
    }
    mx_strcpy(tmp, str);
    
    return result;
}
