#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count)
{
    int l = 0;
    int r = size - 1;
    int coun = 0;

    while (l <= r)
    {
        coun++;
        *count = coun;
        int m = l + (r - l) / 2;

        int count = mx_get_char_index(arr[m], '=');
        if (mx_strncmp(arr[m], s, count) == 0)
        {
            return m;
        }

        if (mx_strncmp(arr[m], s, count) < 0)
        {
            l = m + 1;
        }
        else
        {
            r = m - 1;
        }
    }
    *count = 0;
    return -1;
}
