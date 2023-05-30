
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
