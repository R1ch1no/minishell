
#include "../minishell.h"

void	ft_exec(t_node *node, t_data *data)
{
	(void)node;
	(void)data;
	/* int		count;
	char	*path;
	char	**args;
	t_node	*current;
	t_node	*start;

	current = node->next;
	start = node->next;
	count = 0;
	path = malloc(ft_strlen("/usr/bin/") + ft_strlen(node->cmd) + 1);
	if (!path || path == NULL)
		return ;
	ft_strlcpy(path, "/usr/bin/", (ft_strlen("/usr/bin/") + 1));
	path = ft_strjoin(path, node->cmd);
	if (!path || path == NULL)
		return ;
	if (access(path, F_OK) != 0)
	{
		free(path);
		return ;
	}
	while (current != NULL)
	{
		if (current->special == 1)
			break ;
		count++;
		current = current->next;
	}
	args = malloc((count + 1) * sizeof(char *));
	current = start;
	count = 0;
	while (current != NULL)
	{
		if (current->special == 1)
			break ;
		ft_strlcpy(args[count], current->cmd, ft_strlen(current->cmd) + 1);
		current = current->next;
		count++;
	}
	args[count] = NULL;
	if (execve(path, args, data->env_copy) == -1)
		return ;
	free(path);
	free_2d_str_arr(&args); */
}
