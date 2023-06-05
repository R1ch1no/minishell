
#include "../minishell.h"

//libft alikes
char *ft_str_many_chr(char *str, char *set)
{
    int i;
    int j;

    if (!str || !set)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i])
    {
        while (set[j])
        {
            if (str[i] == set[j])
                return (&str[i]);
            j++;
        }
        j = 0;
        i++;
    }
    return (&str[i]);
}

char *ft_strjoin_3(char *s1, char *s2, char *s3)
{
    char *str;
    char *temp;
    
    if (!s1 || !s2 || !s3)
        return (NULL);
    temp = ft_strjoin(s1, s2);
    if (!temp)
        return (NULL);
    str = ft_strjoin(temp, s3);
    free(temp);
    if (!str)
        return (NULL);
    return (str);
}



//void free_and_null(char *s1)
//{
//    free(s1);
//    free()
//}

void four_free(char *s1, char *s2, char *s3, char *s4)
{
    if (s1)
        free(s1);
    if (s2)
        free(s2);
    if (s3)
        free(s3);
    if (s4)
        free(s4);
}