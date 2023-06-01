
#include "../minishell.h"


//NOTION DIDNT WORK
/*
    $USER">"
    "$USER>"
    $USER>
*/

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

    if (!str)
        return (-1);
    i = 0;
    while (str[i] && ft_strchr(set, str[i]) == NULL) //ends on '\0', space and all special chars
        i++;
    return (i);
}


char *ft_str_many_chr(char *str, char *set)
{
    int i;
    char *ptr;

    if (!str || !set)
        return (NULL);
    i = 0;
    ptr = ft_strchr(set, str[i]);
    while (str[i] && ptr == NULL)
    {
        ptr = ft_strchr(set, str[i]);
        i++;
    }
    return (ptr);
}


char *strdup_without(const char *src, char c, int len)
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

// Test'$USER and $USER' $USER '$USER
//schneid raus quotes wenn gerade und fang danach an
int valid_dollar_sub(char *str, char **env)
{
    int i;

    char *sec_quote;
    char *cutted;
    char *rest;
    //char *str_after
    //char *str_substitute = strdup(cmd_line[])
    i = 0;
    while (str[i])
    {
        if (str[i] == '\'') 
        {
            i++;
            sec_quote = ft_strchr(str, '\'');
            if (sec_quote != NULL)
            {
                cutted = strdup_without(str, '\'', sec_quote - str);
                sec_quote++;
                rest = ft_strdup(sec_quote);
                str = ft_strjoin(cutted, rest);
                free(cutted),
                free(rest);
            }
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
       i++;
    }
}

int subout_dollar(char **str, int i)
{
    char *before_dollar;
    char *dollar_name;
    char *end;
    if (i != 0)
        before_dollar = ft_substr(str, 0, i + 1);
    else
        before_dollar = ft_strdup("");
    end = ft_str_many_chr(&(*str[i]), "$<>|'\" ");
    dollar_name = ft_substr(str, i + 1, end - str[i + 1]);
    printf("dollar_name: %s", dollar_name);
    return (5);
}

//test'$user bla'_'$USER
//test
//'
//$USER bla
//'
//_
//'
//$SUER


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




