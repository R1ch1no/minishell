
#include "../minishell.h"

int single_quotes(char **str, int i, char quote)
{
    int len;
    char *sec_quote;
    char *cutted;
    char *rest;
    
    i++;
    sec_quote = ft_strchr(&(*str)[i], quote);
    if (sec_quote != NULL)
    {
        len = sec_quote - (*str) - 1;
        cutted = strdup_without((*str), quote, len);
        sec_quote++;
        rest = strdup(sec_quote);
        free((*str));
        (*str) = ft_strjoin(cutted, rest);
        free(cutted);
        free(rest);
        i = len;
    }
    return (i);
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
        else if ((*str)[i] == '\'') // && last_quote - 1 < i) //muss noch gefixed werden
            i = single_quotes(str, i, '\'');
        else if ((*str)[i] == '\"')
        {
            last_quote = single_quotes(str, i, '\"');
            if ((*str)[i] == '\"')
                i++;        
        }
        else
            i++;
    }
}
