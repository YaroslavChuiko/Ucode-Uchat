int mx_sqrt(int x)
{
    if (x <= 0)
    {
        return 0;
    }

    double sqrt = x / 2;
    double c = 0;

    while (sqrt != c)
    {
        c = sqrt;
        sqrt = (x / c + c) / 2;
    }

    int result = (int)sqrt;

    if ((sqrt <= 0) || (result != sqrt))
    {
        sqrt = 0;
    }

    return sqrt;
}
