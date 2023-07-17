/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:05:30 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/30 15:18:45 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_and_null(char **str)
{
	free(*str);
	*str = NULL;
}

void	s_d_quotes(char **str)
{
	int	i;
	int	left_for_cut;

	i = 0;
	left_for_cut = FALSE;
	while ((*str) && (*str)[i])
	{
		if (left_for_cut == FALSE && (*str)[i] == '\'' && ft_strchr(&(*str)[i
			+ 1], '\'') != NULL)
			i = single_quotes(str, i, '\'');
		else if ((*str)[i] == '"' && left_for_cut == TRUE)
		{
			strcpy_wout_ind(str, i);
			left_for_cut = FALSE;
		}
		else if ((*str)[i] == '"' && ft_strchr(&(*str)[i + 1], '"') != NULL)
		{
			strcpy_wout_ind(str, i);
			left_for_cut = TRUE;
		}
		else
			i++;
	}
}

int	ft_continue(t_data *data, t_node **current)
{
	t_node	*tmp;

	tmp = NULL;
	if ((*current)->cmd[0] == '\0')
	{
		tmp = (*current)->next;
		delete_node((*current), &data->cmd_line);
		(*current) = tmp;
		if ((*current) != NULL)
			(*current)->prev = NULL;
		return (TRUE);
	}
	return (FALSE);
}

//"$USER"te"st
//here a comment would be nice what the continue is for
//and what the s_d_quotes is for
void	prep_for_executer(t_node **head, t_data *data)
{
	t_node	*current;

	current = *head;
	while (current && current->cmd)
	{
		if (count_char(current->cmd, '"') > 1
			|| count_char(current->cmd, '\'') > 1)
			dollar_and_s_quotes(&(current->cmd), current, data);
		else if (current && ft_strchr(current->cmd, '$') != NULL
			&& check_if_token(current->prev, "<<") == FALSE)
		{
			dollar_and_s_quotes(&(current->cmd), current, data);
			if (ft_continue(data, &current) == TRUE)
				continue ;
		}
		if (current != NULL)
			s_d_quotes(&current->cmd);
		if (current != NULL && current->cmd == NULL)
			malloc_error(data);
		if (current != NULL)
			current = current->next;
	}
}
