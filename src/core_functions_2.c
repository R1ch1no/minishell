
#include "../minishell.h"

//deletes until pipe(inclusive) or null
void	delete_cmd(t_node **head)
{
	t_node	*temp;

	if (*head == NULL)
		return ;
	temp = *head;
	while (temp && check_if_token(temp, "|") == FALSE)
	{
		delete_node(temp, head);
		temp = *head;
	}
	delete_node(temp, head);
}

void	delete_til_pipe(t_node **head)
{
	t_node	*temp;

	if (*head == NULL)
		return ;
	temp = *head;
	while (temp && check_if_token(temp, "|") == FALSE)
	{
		delete_node(temp, head);
		temp = *head;
	}
}
