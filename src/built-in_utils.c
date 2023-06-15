
#include "../minishell.h"

void	echo_print(t_node **node, int n)
{
	int	i;

	while ((*node) != NULL)
	{
		i = -1;
		if ((*node)->special == 1)
			return ;
		while ((*node)->cmd[++i])
		{
			if (n == 1 && (*node)->cmd[i + 1] == '\0'
				&& (*node)->cmd[i] == '\n')
				break ;
			write(1, &(*node)->cmd[i], 1);
		}
		(*node) = (*node)->next;
		if ((*node) != NULL)
			if ((*node)->special != 1)
				write(1, " ", 1);
	}
}
