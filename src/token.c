
#include "../minishell.h"

void	identify_tokens(t_node *head)
{
	t_node	*current;

	current = head;
	while (current)
	{
		if (ft_strcmp_v2(current->cmd, "<") == 0 || ft_strcmp_v2(current->cmd,
				"<<") == 0)
			current->special = TRUE;
		else if (ft_strcmp_v2(current->cmd, ">") == 0
			|| ft_strcmp_v2(current->cmd, ">>") == 0)
			current->special = TRUE;
		else if (ft_strcmp_v2(current->cmd, "|") == 0)
			current->special = TRUE;
		current = current->next;
	}
}

int	check_if_token(t_node *node, char *token)
{
	if (!node || node == NULL || !token)
		return (FALSE);
	if (ft_strcmp_v2(node->cmd, token) == 0 && node->special == 1)
		return (TRUE);
	return (FALSE);
}

int	check_if_any_token(t_node *node)
{
	if (!node)
		return (FALSE);
	if (check_if_token(node, "|") == TRUE)
		return (TRUE);
	if (check_if_token(node, "<") == TRUE)
		return (TRUE);
	if (check_if_token(node, "<<") == TRUE)
		return (TRUE);
	if (check_if_token(node, ">") == TRUE)
		return (TRUE);
	if (check_if_token(node, ">>") == TRUE)
		return (TRUE);
	return (FALSE);
}
