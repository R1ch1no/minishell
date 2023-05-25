
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


//if u find dollar then subout except above and then check further but at last dollar + strlen env_var sub
//dollar sign var stops until:
// any redirection 
//dollar again
//pipe
//quotes kinda weird

int valid_dollar_sub(char *str)
{
    int i;
    int quotes;


    i = 0;
    quotes = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            quotes++;
        else if (str[i] == '$')
        {
            if (!(quotes % 2 != 0 && ft_strchr(&str[i], '\'') != NULL)) //if dollar is negated cuz of single quotes
                subout_dollar;
                i+=ka;
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
