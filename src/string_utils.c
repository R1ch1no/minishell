
#include "../minishell.h"

//without a specific char
char *strdup_without(char *src, char c, int len)
{
    char *dup;
    int i;
    int j;

    if (!src)
        return (NULL);
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        exit(1); //cleanse()
    i = 0;
    j = 0;
    while (src[i] && j < len)
    {
        if (src[i] != c)
        {
            dup[j] = src[i];
            j++;
        }
        i++;
    }
    dup[j] = '\0';
    return (dup);
}

//copies the str without one index
void strcpy_wout_ind(char **str, unsigned int x, t_data *data)
{
    unsigned int i;
    unsigned int j;
    char *cpy;
        
    cpy = malloc(sizeof(char) * ft_strlen(*str));
    if (!cpy)
        cleanse(data);
    i = 0;
    j = 0;
    while ((*str)[i])
    {
        if (i != x)
        {
            cpy[j] = (*str)[i];
            i++;
            j++;
        }
        else
            i++;   
    }
    cpy[j] = '\0';
    free(*str);
    *str = cpy;
}

int check_if_char_in_row(char *str, char c)
{
    int i;
    
    i = 0;
    
    if (!str)
        return (-1);
    if (str[i] == c && str[i + 1] == c)
        return (TRUE);
    else
        return(FALSE);
}

int get_index_of(char *str, char c)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}