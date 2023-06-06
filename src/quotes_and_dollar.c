
#include "../minishell.h"


//int double_quote_exception(char **str, int i char quote)
//{
//    char *cutted;
//    char *rest;
//
//    cutted = ft_substr((*str), 0, i +1);
//    rest = ft_strdup((*str)[i]);
//}

//int cut_sec_quote(char **str, int i, int *statisch)
//{
//    char *cutted;
//    char *rest;
//
//    printf("FOUND SEC Q INDEX\n");
//    strcpy_wout_ind(str, i, NULL);
//    return (i);
//
//    cutted = ft_substr((*str), 0, i); //cuz i cutted 
//    rest = ft_strdup(&(*str)[i + 1]);
//    statisch = -1;
//
//    if (!cutted || !rest )
//    {
//        free(*str);
//        *str = NULL;
//        return (-1);
//    }
//    free((*str));
//    (*str) = ft_strjoin(cutted, rest); //if fail then str = NULL and it will be detected
//    printf("double quote str: %s\n", *str);
//    free(cutted);
//    free(rest);
//    return (0);
//}

int double_quotes(char **str, int i, char quote)
{   
    //similar to single but it only cuts out the first quote
    int len;
    char *sec_quote;
    char *cutted;
    char *rest;
    //static int sec_q_index;
//
    //if (!sec_q_index)
    //    sec_q_index = -1;
    //printf("SEC Q INDEX: %d, i: %d\n", sec_q_index, i);
    //if (sec_q_index != -1 && sec_q_index == i)
    //    return (cut_sec_quote());   
    //12"$5678"end
    if (1) 
    {
        sec_quote = ft_strchr(&(*str)[i + 1], quote);
        len = sec_quote - (*str) - 1;
        //sec_q_index = i + len - 2;// + 1;
        cutted = strdup_without((*str), quote, len);
        rest = ft_strdup(sec_quote);
        i = len;
        //printf("SEC Q INDEX: %d, i: %d\n", sec_q_index, i);
    }
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
    //printf("double quote str: %s\n", *str);
    free(cutted);
    free(rest);
    return (i);
}


int single_quotes(char **str, int i, char quote)
{
    int len;
    char *sec_quote;
    char *cutted;
    char *rest;
    //12'$5678'end
    //10 -2 = 8
    sec_quote = ft_strchr(&(*str)[i + 1], quote);
    len = sec_quote - &(*str)[i] - 1;
    cutted = strdup_without(&(*str)[i + 1], quote, len);
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
    //i = len;
    //return (len);
    return (i);
}



//only works with malloc'd str
//j is to "remember" the ending double quote if before it is $ then skip substitution and to not subout single quotes
void dollar_and_s_quotes(char **str, t_data *data) 
{
    int i;
    int last_quote;
    int left_for_cut;
    //int len;
    
    i = 0;
    last_quote = 0;
    left_for_cut = FALSE;
    while ((*str) && (*str)[i])
    {
        if ((*str)[i] == '$' && last_quote - 1 != i)//&& (*str)[i + 1] && (*str)[i + 1] != ' ' )
        {
            //if (i < last_quote)
            i = subout_dollar(str, i, data);
        }  
        else if ((*str)[i] == '\'' && ft_strchr(&(*str)[i + 1], '\'') != NULL && last_quote - 1 < i) //muss noch gefixed werden
            i = single_quotes(str, i, '\'');
        else if ((*str)[i] == '\"' && left_for_cut)
        {
            strcpy_wout_ind(str, i, data);
            left_for_cut = FALSE;
        }
        else if ((*str)[i] == '\"' && ft_strchr(&(*str)[i + 1], '\"') != NULL)
        {
            //last_quote = single_quotes(str, i, '\"');
            last_quote = double_quotes(str, i, '\"');
            left_for_cut = TRUE;
            //if ((*str)[i] == '\"' && count_char(&(*str)[i], '\"') == 1)
            //  i++;
        }
        else
            i++;
        //i += len;
    }
}

