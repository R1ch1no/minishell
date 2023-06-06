
#include "../minishell.h"


int double_quotes(char **str, int i, char quote)
{   
    //similar to single but it only cuts out the first quote
    int len;
    char *sec_quote;
    char *cutted;
    char *rest;
    static int sec_q_index;
    //12"$5678"end
    sec_quote = ft_strchr(&(*str)[i + 1], quote);
    len = sec_quote - (*str) - 1;
    sec_q_index = i + len;
    cutted = strdup_without((*str), quote, len);
    sec_quote++;
    rest = ft_strdup(sec_quote);
    if (!cutted || !rest )
    {
        free(*str);
        *str = NULL;
        return (-1);
    }
    free((*str));
    (*str) = ft_strjoin(cutted, rest); //if fail then str = NULL and it will be detected
    free(cutted);
    free(rest);

    return (len);
}



int single_quotes(char **str, int i, char quote)
{
    int len;
    char *sec_quote;
    char *cutted;
    char *rest;
    //12"$5678"end
    i++;
    sec_quote = ft_strchr(&(*str)[i], quote);
    len = sec_quote - (*str) - 1;
    cutted = strdup_without((*str), quote, len);
    sec_quote++;
    rest = ft_strdup(sec_quote);
    if (!cutted || !rest )
    {
        if (cutted)
            free(cutted);
        free(*str);
        *str = NULL;
        return (-1);
    }
    free((*str));
    (*str) = ft_strjoin(cutted, rest); //if fail then str = NULL and it will be detected
    free(cutted);
    free(rest);
    return (len);
}

//only works with malloc'd str
//j is to "remember" the ending double quote if before it is $ then skip substitution and to not subout single quotes
void dollar_and_s_quotes(char **str, t_data *data) 
{
    int i;
    int last_quote;
    
    i = 0;
    last_quote = 0;
    while ((*str) && (*str)[i])
    {
        if ((*str)[i] == '$' && last_quote - 1 != i)//&& (*str)[i + 1] && (*str)[i + 1] != ' ' )
        {
            //if (i < last_quote)
            i = subout_dollar(str, i, data);
        }  
        else if ((*str)[i] == '\'' && ft_strchr(&(*str)[i + 1], '\'') != NULL) // && last_quote - 1 < i) //muss noch gefixed werden
            i = single_quotes(str, i, '\'');
        else if ((*str)[i] == '\"' && ft_strchr(&(*str)[i + 1], '\"') != NULL)
        {
           last_quote = single_quotes(str, i, '\"');
           if ((*str)[i] == '\"' && count_char(&(*str)[i], '\"') == 1)
               i++;
        }
        else
            i++;
    }
}

