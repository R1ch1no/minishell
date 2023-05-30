
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
		free(current->next);
		current->next = NULL;
	}
	free(data->cmd_line->cmd);
	free(data->cmd_line);
	data->cmd_line = NULL;
}

void	add_node_back(t_node **lst, t_node *new)
{
	t_node	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	last = lstlast(*lst);
	last->next = new;
}

t_node	*create_node(char *str)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		return (NULL);
	printf("Node created\n");
	new->cmd = str;
	new->next = NULL;
	return (new);
}

