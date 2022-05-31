int mx_strncmp(const char *s1, const char *s2, int n)
{
    int index = 0;
    while (index < n)
    {
        if (s1[index] != s2[index])
        {
            return s1[index] - s2[index];
        }
        index++;
    }
    return 0;
}
