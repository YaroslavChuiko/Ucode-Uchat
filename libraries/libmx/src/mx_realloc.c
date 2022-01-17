#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
    {
        return malloc(size);
    }
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }
    #ifdef __MACH__
        if (size <= malloc_size(ptr))
        {
            return ptr;
        }
    #else
        if (size <= malloc_usable_size(ptr))
        {
            return ptr;
        }
    #endif

    void *new_ptr = malloc(size);

    #ifdef __MACH__
        mx_memcpy(new_ptr, ptr, malloc_size(ptr));
    #else
        mx_memcpy(new_ptr, ptr, malloc_usable_size(ptr));
    #endif

    free(ptr);
    
    return new_ptr;
}
