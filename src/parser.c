
#include "../minishell.h"

static void	token_err_msg(char *tokentype)
{
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	ft_putstr_fd(": error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(tokentype, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

//BASH IS DUMP0 dont want to handle it << eof wc < >
int	parser(t_node *list)
{
	if (!list)
		return (ERROR);
	if (check_if_token(list, "|") == TRUE)
	{
		ft_putstr_fd(PROMPT, STDERR_FILENO);
		ft_putstr_fd(": syntax error near unexpected token `|'\n",
			STDERR_FILENO);
		return (ERROR);
	}
	while (list->next)
	{
		if (check_if_any_token(list) == TRUE
			&& check_if_any_token(list->next) == TRUE && check_if_token(list,
				"|") == FALSE)
			return (token_err_msg(list->next->cmd), ERROR);
		list = list->next;
	}
	if (check_if_any_token(list) == TRUE)
	{
		ft_putstr_fd(PROMPT, STDERR_FILENO);
		ft_putstr_fd(": syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (ERROR);
	}
	return (0);
}
