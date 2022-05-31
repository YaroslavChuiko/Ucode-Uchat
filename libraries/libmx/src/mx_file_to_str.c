#include "../inc/libmx.h"

char *mx_file_to_str(const char *file)
{
    if (!file)
    {
        return NULL;
    }

    int file_des;

    if ((file_des = open(file, O_RDONLY)) < 0)
    {
        return NULL;
    }

    char *result = NULL;
    char buffer[1];
    int size = read(file_des, buffer, 1);
    int length = 0;

    while (size)
    {
        size = read(file_des, buffer, 1);
        length++;
    }

    if (close(file_des) < 0)
    {
        return NULL;
    }

    if (length >= 0)
    {
        result = mx_strnew(length);

        if ((file_des = open(file, O_RDONLY)) < 0)
        {
            return NULL;
        }

        size = read(file_des, &buffer, 1);

        for (int i = 0; size; i++)
        {
            result[i] = buffer[0];
            size = read(file_des, buffer, 1);
        }

        if (close(file_des) < 0)
        {
            return NULL;
        }
    }

    return result;
}
