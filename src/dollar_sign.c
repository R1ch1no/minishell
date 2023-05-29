
#include "../minishell.h"

//123456
//abcdef
//012345

/*
'$'money_file
check if dollar sub valid returns int
if that int not -1 then i have index of where the dollar is in the str
*/


//recipe:
//cuting out all double quotes "" before dollar sign should be fine
//gerade=alle raus, ungerade alle außer das letzte raus


int get_len_til(char *str, char *set)
{
    int i;

    i = 0;
    while (str[i] && ft_strchr(set, str[i]) == NULL) //ends on '\0', space and all special chars
        i++;
    return (i);
}

// Test'$USER and $USER' $USER '$USER
//schneid raus quotes wenn gerade und fang danach an
int valid_dollar_sub(char *str, char **env)
{
    int i;
    int quotes;
    char *before_dollar;
    char *after_dollar;
    char *env_value;
    //char *str_after
    //char *str_substitute = strdup(cmd_line[])

    i = 0;
    quotes = 0;
    while (str[i])
    {
        if (str[i] == '\'' && ft_strchr(str, '\'') != NULL)
            cut_out_all
        else if (str[i] == '$')
        {
            if ((quotes % 2 != 0 && ft_strchr(&str[i], '\'') != NULL)) //if dollar is negated cuz of single quotes
                i++;
            else
            {
                if (i != 0)
                    before_dollar = ft_substr(str, 0, i + 1);
                after_dollar = ft_substr(str, i + 1, get_len_til(&str[i], "$<>|'\""));
                env_value = get_env_value(after_dollar);
            }
            //substr str_before_$ (str[0], len=i+1) if i = 0 dann len = 0
            //get str_after_$_til: space or eof or $
            //look for it in env_copy
            //if exists then get ="value"
                //env_len = ft_strlen(ft_strchr)
                //substr(ft_strchr("="))
            //else
                //empty string
            //join with str_before_$
            //strlen of joined str
            //set i to the next char after the end of last $VAR
            //free str_before and str_after and str from cmd_line
            //set str to joined str!    
        }
       i++;
    }
}



//test'$user bla'_'$USER

//test
//'
//$USER bla
//'
//_
//'
//$SUER



void dollar_and_s_quotes(char *str)
{
    int i;
    int count;
    char **temp;
    
    i = 0;
    count = count_char(str, '\'');
    if (count == 1)
    {
        while(str[i]) 
        {
            if (str[i] == '$')
                printf("");
            i++;
        }
        return ;
    }

    temp = ft_split(str, '\'');
}


int get_arr_len(char **arr)
{
    int i;

    i = 0;
    if (!arr)
        return (-1);
    while (arr[i])
        i++;
    return (i);
}

int get_i_of_next_occ(char **arr, int first, char *str)
{
    int i;

    if (!arr || !str)
       return (-1);
    i = first + 1;
    while (arr[i] && ft_strcmp_v2(arr[i], str) != 0)
       i++;
    if (arr[i] == NULL)
        return (-1);
    return (i);
}

//LETS SAY I HAVE A SPLIT IN MY WAY MEANING all words and the spliter
char *subout_dollar_s_quotes(char **arr)
{
    int i;
    int j;
    char *temp;
    char *buf;

    temp = ft_strjoin("", "");
    i = 0;
    while (arr[i])
    {
        if (arr[i][0] == '\'' && arr[i + 2][0])
        {
            //ES KANN NUR 1 str zwischen splitter SEIN
            free(arr[i]);
            arr[i] = malloc(sizeof(char));
            arr[i][0] = '\0';
            i += 2;
            free(arr[i]);
            arr[i] = malloc(sizeof(char));
            arr[i][0] = '\0';
        }
        if (count_char(arr[i], '$'))
            subout_dollar();
        else if (i != 0)
            temp = ft_strjoin(temp, arr[i]);

    }
    return (temp)
}






int single_quote_exception(char *str, int quotes)
{
    if (quotes % 2 != 0 && ft_strchr(str, '\'') != NULL)
        return (TRUE);
    else 
        return(FALSE);
}
