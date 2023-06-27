
#include "../minishell.h"

int	before_start(t_node *node)
{
	DIR	*dir;

	if (ft_strcmp_v2_until(node->cmd, "./", '/') == 0
		|| ft_strcmp_v2_until(node->cmd, "/", '/') == 0)
	{
		dir = opendir(node->cmd);
		if (dir != NULL)
		{
			closedir(dir);
			return (ft_putstr_fd("Is a directory\n", 2), IS_DIR);
		}
	}
	return (0);
}
