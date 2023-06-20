
#include "../minishell.h"

void	prep_for_executer(t_node **head, t_data *data)
{
	t_node	*current;

	current = *head;
	//printf("PREP EXEC\n");
	while (current)
	{
		if (count_char(current->cmd, '\'') > 1 || count_char(current->cmd,
				'"') > 1 || ft_strchr(current->cmd, '$') != NULL)
			dollar_and_s_quotes(&(current->cmd), data);
		//if (current->cmd == NULL)
		//	cleanse(data);
		//printf("quotes and dollar: %s\n", current->cmd);
		//printf("special value: %d\n", current->special);
		//printf("------------\n");
		current = current->next;
	}
}