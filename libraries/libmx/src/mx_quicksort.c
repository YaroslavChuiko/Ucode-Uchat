#include "../inc/libmx.h"

int mx_quicksort(char **arr, int left, int right)
{
    if (!arr)
    {
        return -1;
    }

    int counter = 0;

    if (left < right)
    {
        int pivot = mx_strlen(arr[(left + right) / 2]);
        int l = left;
        int r = right;

        while (l <= r)
        {
            while (mx_strlen(arr[l]) < pivot) l++;
            while (mx_strlen(arr[r]) > pivot) r--;

            if (l <= r)
            {
                if (mx_strlen(arr[l]) != mx_strlen(arr[r]))
                {
                    char *tmp;
                    tmp = arr[l];
                    arr[l] = arr[r];
                    arr[r] = tmp;

                    counter++;
                }

                l++;
                r--;
            }
        }

        counter += mx_quicksort(arr, left, r);
        counter += mx_quicksort(arr, l, right);
    }

    return counter;
}
