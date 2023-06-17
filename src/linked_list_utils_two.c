
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
	if (!delete || delete == NULL || *head == NULL)
		return ;
	if (delete == *head)
		*head = (*head)->next;
	else if (delete->next == NULL)
		delete->prev->next = NULL;
	else
	{
		delete->prev->next = delete->next;
		delete->next->prev = delete->prev;
	}
	free(delete->cmd);
	free(delete);
}
