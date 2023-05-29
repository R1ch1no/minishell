
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
//wenn ich quotes for dollar zähle dann kann ich sie schon rausschneiden

void preparing_dollar_for_executer(t_data *data)
{
    int i;
    
    i = 0;
    while (data->cmd_line[i])
    {
        if (valid_dollar_sub())
            subout_dollar();
        else 
            i++;
    }


}

//if u find dollar then subout except above and then check further but at last dollar + strlen env_var sub
//dollar sign var stops until:
// any redirection 
//dollar again
//pipe
//quotes kinda weird


char *get_env_value(char **env) //nach dem ersten = Zeichen
{
    return ("end");
}

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
        if (str[i] == '\'' && ft_strchr(str, '\''))
            quotes++; //cut out quotes 
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




int single_quote_exception(char *str, int quotes)
{
    if (quotes % 2 != 0 && ft_strchr(str, '\'') != NULL)
        return (TRUE);
    else 
        return(FALSE);
}
