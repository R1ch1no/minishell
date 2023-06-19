
#include "../minishell.h"

//runs an executable from the current folder with ./
int	ft_exec_here(char **path, t_node *node, char ***args)
{
	*path = malloc(ft_strlen(node->cmd) + 1);
	if (!path || path == NULL)
		return (write(2, "Allocation (ft_exec) problem!\n", 30) && 1);
	ft_strlcpy(*path, node->cmd, ft_strlen(node->cmd) + 1);
	*args = malloc((arg_num(node) + 1) * sizeof(char *));
	if (!args || args == NULL)
	{
		free(*path);
		return (write(2, "Allocation (ft_exec) problem!\n", 30) && 1);
	}
	return (0);
}

int	ft_exec_path(char **pre_path, char **path, t_node *node, char ***args)
{
	*pre_path = malloc(ft_strlen("/usr/bin/") + ft_strlen(node->cmd) + 1);
	if (!pre_path || pre_path == NULL)
		return (write(2, "Allocation (ft_exec) problem!\n", 30) && 1);
	ft_strlcpy(*pre_path, "/usr/bin/", (ft_strlen("/usr/bin/") + 1));
	*path = exec_strjoin(*pre_path, node->cmd);
	if (!path || path == NULL)
		return (write(2, "Allocation (ft_exec) problem!\n", 30) && 1);
	*args = malloc((arg_num(node) + 1) * sizeof(char *));
	if (!args || args == NULL)
	{
		free(*path);
		free(*pre_path);
		return (write(2, "Allocation (ft_exec) problem!\n", 30) && 1);
	}
	return (0);
}
