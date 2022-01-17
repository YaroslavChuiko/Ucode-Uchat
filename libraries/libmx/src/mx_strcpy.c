char *mx_strcpy(char *dst, const char *src)
{
    char *s = dst;
    while (*src != '\0')
    {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    return s;
}
