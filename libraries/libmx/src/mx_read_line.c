#include "../inc/libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd)
{
    if (lineptr == NULL || buf_size < 0 || fd < 0)
    {
        return -2;
    }

    *lineptr = mx_realloc(*lineptr, buf_size);
    // #ifdef __MACH__
        mx_memset(*lineptr, '\0', malloc_size(*lineptr));
    // #else
        // mx_memset(*lineptr, '\0', malloc_usable_size(*lineptr));
    // #endif

    char ch;
    buf_size = 1;
    size_t counter = 0;

    for(; read(fd, &ch, buf_size) > 0; counter++)
    {
        if (ch == delim)
        {
            return counter;
        }

        if (counter >= buf_size)
        {
            *lineptr = mx_realloc(*lineptr, counter + 1);
        }

        (*lineptr)[counter] = ch;
    }

    if (counter == 0)
    {
        return -1;
    }

    #ifdef __MACH__
        mx_memset(&(*lineptr)[counter], '\0', malloc_size(*lineptr) - counter);
    #else
        mx_memset(&(*lineptr)[counter], '\0', malloc_usable_size(*lineptr) - counter);
    #endif
    
    return counter;
}
