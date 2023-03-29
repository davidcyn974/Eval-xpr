int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;
    while (((s1[i] == s2[i])) && ((s1[i] != '\0') && (s2[i] != '\0')))
    {
        i++;
    }
    if (s1[i] == s2[i])
    {
        return 0;
    }
    else if (s1[i] < s2[i])
    {
        return -44;
    }
    return 22;
}
