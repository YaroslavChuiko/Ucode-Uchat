#include "../inc/libmx.h"

bool cmp_strings(const char* a, const char* b) {

    return mx_strcmp(a, b) > 0;

}

bool cmp_strings_r(const char* a, const char* b) {

    return mx_strcmp(a, b) < 0;

}

int mx_bubble_sort(char **arr, int size, bool (*cmp)(const char* a, const char* b))
{
    int noSwap;
    char *tmp;
    int swap = 0;

    for (int i = 0; i < size - 1; i++)
    {
        noSwap = 1;

        for (int j = 0; j < size - 1 - i; j++)
        {
            if (cmp(arr[j], arr[j + 1]))
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                noSwap = 0;
                swap++;
            }
        }

        if (noSwap == 1)
        {
            break;
        }
    }
    
    return swap;
}
