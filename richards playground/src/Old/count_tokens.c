void check_redirections(char *str, int *i)
{
    if (str[*i] == '<' || str[*i] == '>')
    {
        (*i)++;
        if (str[*i - 1] == '<' && str[*i] == '<')
            (*i)++;
        else if (str[*i - 1] == '>' && str[*i] == '>')
            (*i)++;
    }
    else
        (*i)++;
}

int count_tokens(char *str, char *set)
{
    int i;
    int count;

    count = 0;
    i = 0;
    while (str[i])
    {
        if (ft_strchr(set, str[i]) != NULL)
        {
            count++;
            check_redirections(str, &i);
        }
        else if (str[i] && str[i] != ' ')
        {
            count++;
            while (str[i] && ft_strchr(set, str[i]) == NULL && str[i] != ' ') 
                i++;
        }
        while (str[i] && str[i] == ' ')
            i++;
        //printf("_%c_ at index i: %d\n", str[i], i);
    }
    printf("Tokens: %d at end of counter function\n", count);
    return (count);
}