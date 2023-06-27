
#include "../minishell.h"

void	prep_for_executer(t_node **head, t_data *data)
{
	t_node	*current;

	current = *head;
	while (current)
	{
		if (count_char(current->cmd, '\'') > 1 || count_char(current->cmd,
				'"') > 1 || ft_strchr(current->cmd, '$') != NULL)
			dollar_and_s_quotes(&(current->cmd), data);
		current = current->next;
	}
}
