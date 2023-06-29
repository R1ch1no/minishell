
#include "../minishell.h"

int	was_child(t_node *current, char ***args)
{
	int	status;

	status = 1;
	if (ft_strcmp_node(current, "unset") == 0)
		status = 0;
	else if (ft_strcmp_node(current, "exit") == 0)
		status = 0;
	else if (ft_strcmp_node(current, "cd") == 0)
		status = 0;
	else if (ft_strcmp_node(current, "export") == 0 && (*args)[1] != NULL)
		status = 0;
	free_2d_str_arr(args);
	return (status);
}
