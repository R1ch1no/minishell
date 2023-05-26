
#include "../minishell.h"

//DOLLAR SIGN ISNT IMPLEMENTED YET

int	count_tokens_v2(char *str) //basically the function below without mallocs
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	while (str[i])
	{
		len = get_token_len(&str[i]);
		j++;
		i += len;
		while (str[i] == ' ')
			i++;
	}
	//printf("Token count v2: %d\n", j);
	return (j);
}

void	init_cmd_line(t_data *data)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	str = data->line_read;
	i = 0;
	j = 0;
	while (str[i])
	{
		len = get_token_len(&str[i]);
		data->cmd_line[j] = ft_substr(str, i, len);
		if (data->cmd_line[j] == NULL)
			return (perror("minishell malloc"), cleanse(data));
		//evtl exit aus cleanup rausnehmen? und in solchen Fällen exit(1)?
		j++;
		i += len;
		while (str[i] == ' ')
			i++;
	}
	data->cmd_line[j] = NULL;
	//printf("____Testing init 2d cmd_line array______\n");
	print_str_arr(data->cmd_line);
}

int	get_token_len(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr("|<>", str[i]) != NULL)
		return (get_non_quote_len(str));
	while (str[i] && ft_strchr("|<> ", str[i]) == NULL)
	{
		if (str[i] == '\'' || str[i] == '\"')
	    {
			i += get_quote_len(&str[i]);
			//printf("get_token_len: %s\n", &str[i]);
		}	
		else
			i++;
	}
	return (i);
}

//int get_non_quote_len(char *str, int i)
//{
//    if (str[i] == '<' || str[i] == '>')
//    {
//        i++;
//        if (str[i - 1] == '<' && str[i] == '<')
//            i++;
//        else if (str[i - 1] == '>' && str[i] == '>')
//            i++;
//    }
//    else
//        i++;
//    return (i);
//}

//either returns 1 or 2
int	get_non_quote_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '<' || str[i] == '>')
	{
		i++;
		if (str[i - 1] == '<' && str[i] == '<')
			i++;
		else if (str[i - 1] == '>' && str[i] == '>')
			i++;
	}
	else if (str[i] == '|')
		i++;
	return (i);
}

//
int	get_quote_len(char *str)
{
	int		i;
	char	*closing_quote;

	//printf("___get_quote_token_len_______\n");
	i = 0;
	if (str[i] == '\'')
	{
		closing_quote = ft_strchr(&str[i + 1], '\'');
		if (closing_quote != NULL)
			return (closing_quote - &str[i] + 1); //if this ret-value is added to the first quote then u will land on the second quote 
	}
	else if (str[i] == '\"')
	{
		closing_quote = ft_strchr(&str[i + 1], '\"');
		if (closing_quote != NULL)
		{
			//printf("pointer diff: %ld\n", closing_quote - &str[i]);
			return (closing_quote - &str[i] + 1);
		}
	}
	return (1);
}
