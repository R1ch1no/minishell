
#include "../minishell.h"

void	print_list(t_node *head)
{
	t_node	*print;

	if (!head)
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

void	delete_node(t_node *delete)
{
	t_node *prev;
	t_node *next;

	//prev = delete->prev;
	next = delete->next;
	prev->next = next;
	//next->prev = prev;
	free(delete->cmd);
	delete->cmd = NULL;
	free(delete);
	delete = NULL;
}