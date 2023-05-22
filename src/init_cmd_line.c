/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:45:09 by qtran             #+#    #+#             */
/*   Updated: 2023/05/22 17:36:50 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	//figured this part is not needed At ALL
	//else if (str[i] == '\'' || str[i] == '\"')
	//    i = get_quote_len(&str[i]);
	while (str[i] && (str[i] != ' ' && ft_strchr("|<>", str[i]) == NULL))
		i++;
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

//entire thing not needed i think WTF AM I BAD
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
			return (closing_quote - &str[i] + 1);
	}
	else if (str[i] == '\"')
	{
		closing_quote = ft_strchr(&str[i + 1], '\"');
		if (closing_quote != NULL)
			return (closing_quote - &str[i] + 1);
	}
	return (1);
}
