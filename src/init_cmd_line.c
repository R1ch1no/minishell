/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:05:05 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/30 15:20:20 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//data->line_read is typecasted for shorter lines into char *str
void	init_cmd_line(t_data *data)
{
	int		i;
	int		len;
	char	*str;
	char	*cmd_str;
	t_node	*new_node;

	str = data->line_read;
	i = 0;
	new_node = NULL;
	while (str[i])
	{
		len = get_token_len(&str[i]);
		cmd_str = ft_substr(str, i, len);
		new_node = create_node(cmd_str);
		if (cmd_str == NULL || new_node == NULL)
			return (free(cmd_str), malloc_error(data));
		add_node_back(&data->cmd_line, new_node);
		i += len;
		while (str[i] && str[i] == ' ')
			i++;
	}
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
			i += get_quote_len(&str[i]);
		else
			i++;
	}
	return (i);
}

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

//return the len of the str in quotes
//if this ret-value is added to the first quote
//then u will land on the second quote
int	get_quote_len(char *str)
{
	int		i;
	char	*closing_quote;

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
		{
			return (closing_quote - &str[i] + 1);
		}
	}
	return (1);
}
