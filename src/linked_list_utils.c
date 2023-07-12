/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:05:16 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/29 18:05:17 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*lstlast(t_node *lst)
{
	t_node	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_node	*lstlastsec(t_node *lst)
{
	t_node	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next->next)
		temp = temp->next;
	return (temp);
}

void	ft_clean_cmd(t_data *data)
{
	t_node	*current;
	t_node	*start;

	start = data->cmd_line;
	if (start == NULL)
		return ;
	while (start->next)
	{
		current = lstlastsec(data->cmd_line);
		free(current->next->cmd);
		current->next->cmd = NULL;
		free(current->next);
		current->next = NULL;
	}
	free(data->cmd_line->cmd);
	data->cmd_line->cmd = NULL;
	free(data->cmd_line);
	data->cmd_line = NULL;
}

void	add_node_back(t_node **lst, t_node *new)
{
	t_node	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = lstlast(*lst);
	last->next = new;
	new->prev = last;
}
