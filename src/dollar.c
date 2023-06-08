
#include "../minishell.h"

char *get_str_before_dollar(char *str, int i)
{
    char *before_dollar;
    if (i != 0)
        before_dollar = ft_substr(str, 0, i - 1);
    else
        before_dollar = ft_strdup("");
    return (before_dollar);
}

//it can have spaces and <> signs if its in double quotes, bash reads the name until the special chars
//fixes bug if unclosed quote after $ sign: $name" or $"name 
char *get_end_of_dollar(char *str, int i, int left_for_cut)
{
    char *end;
    int n_single;
    int n_double;
    //int i_single;
    //int i_double;
    
    n_single = count_char(str, '\'');
    //i_single = get_index_of(str, '\'');
    n_double = count_char(str, '"');
    //i_double = get_index_of(str, '"');

    if (left_for_cut == TRUE && n_single > 1)
        end = ft_str_many_chr(&str[i], "'\"$?<>| ");
    else if (left_for_cut == TRUE)
        end = ft_str_many_chr(&str[i], "\"$?<>| ");
    else if (n_single == 0 && n_double > 1)
        end = ft_str_many_chr(&str[i], "\"$?<>| ");
    else if (n_single <= 1 && n_double <= 1)
        end = ft_str_many_chr(&str[i], "$?<>| ");
    else
        end = ft_str_many_chr(&str[i], "'\"$?<>| ");
    return (end);
}

char *get_env_value(char c, char **end_of_d)
{
    char *env_value;
    
    if (c == '?')
    {
        env_value = ft_strdup("1234");
        (*end_of_d)++;
    }
    else
        env_value = ft_strdup("qtran");
    return (env_value);
}

int subbing_cmd_str(char **str, char *before_d, char *env_value, char *end_of_d)
{
    char *after_d;
    
    if (*end_of_d != '\0')
    {
        after_d = ft_strdup(end_of_d);
        if (!after_d)
            return (1);
        free(*str);
        (*str) = ft_strjoin_3(before_d, env_value, after_d);
        if ((*str) == NULL)
            return (1);
        free(after_d);
    }
    else
    {
        free(*str);
        *str = ft_strjoin(before_d, env_value);
        if ((*str) == NULL)
            return (1);
    }
    return (0);
}

int check_if_quote_and_closed(char *str, int i)
{
    if (str[i] == '\'' && ft_strchr(&str[i + 1], '\'') != NULL)
        return (TRUE);
    else if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"') != NULL)
        return (TRUE);
    return (FALSE);
}

//int edge_cases()

int subout_dollar(char **str, int i, int left_f_cut, t_data *data)
{
    char *before_d;
    char *d_name;
    char *env_value;
    char *end_of_d;

    i++;
    if (ft_strchr("<>| \0", (*str)[i]) != NULL)
        return (1);
    if (check_if_quote_and_closed((*str), i) == TRUE && left_f_cut == TRUE)
        return (1);
    if ((*str)[i] == '"' && left_f_cut == TRUE)
        return (1);
    if (check_if_quote_and_closed((*str), i) == TRUE || (left_f_cut == TRUE && (*str)[i] == '"'))
        return (strcpy_wout_ind(str, i - 1, data), 0);
    before_d = get_str_before_dollar(*str, i);
    end_of_d = get_end_of_dollar(*str, i, left_f_cut);
    d_name = ft_substr(*str, i, end_of_d - &(*str)[i]);
    env_value = get_env_value((*str)[i], &end_of_d);
    if ((!before_d) || (!end_of_d) || (!d_name) || (!env_value))
        cleanse(data);
    if (subbing_cmd_str(str, before_d, env_value, end_of_d) == 1)
        cleanse(data);
    four_free(d_name, before_d, env_value, NULL);
    return (ft_strlen(env_value) - 1);
}

