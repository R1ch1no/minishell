
#include "../minishell.h"


/*

'$'money_file
check if dollar sub valid returns int
if that int not -1 then i have index of where the dollar is in the str

*/


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

int i = ft_substr();


//if u find dollar then subout except above and then check further but at last dollar + strlen env_var sub
//dollar sign var stops until:
// any redirection 
//dollar again
//pipe
//quotes kinda weird

int valid_dollar_sub(char *str, char **env)
{
    int i;
    int quotes;
    //char *str_before
    //char *str_after
    //char *str_substitute = strdup(cmd_line[])

    i = 0;
    quotes = 0;
    if (str[i] == '$')
        //wie unten außer substr_before
        return 
    while (str[i])
    {
        if (str[i] == '\'')
            quotes++;
        else if (str[i] == '$')
        {
            if ((quotes % 2 != 0 && ft_strchr(&str[i], '\'') != NULL)) //if dollar is negated cuz of single quotes
                i++;
            else
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
        else 
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
