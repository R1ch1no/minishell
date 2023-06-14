
#include "../minishell.h"

void	print_list(t_node *head)
{
	t_node	*print;

	if (!head || head == NULL)
		return ;
	print = head;
	ft_printf("----Start-----\n");
	while (print)
	{
		ft_printf("node: %s\n", print->cmd);
		print = print->next;
	}
	ft_printf("----End-----\n");
}

//it is not doing anything, pointers are lost, node gets deleted
void	delete_node(t_node *delete, t_node **head)
{
	t_node	*prev;
	t_node	*next;

	if (!delete || delete == NULL || *head == NULL)
		return ;
	prev = delete->prev;
	next = delete->next;
	if (prev == NULL)
		*head = next;
	else if (next == NULL)
		prev->next = NULL;
	else
	{
		next->prev = prev;
		prev->next = next;
	}
	free(delete->cmd);
	free(delete);
}
