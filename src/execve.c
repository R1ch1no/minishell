
#include "../minishell.h"

void	ft_exec(t_node *node, t_data *data, char **env)
{
	int		count;
	char	*path;
	char	**args;
	t_node	*current;
	t_node	*start;

	(void)data;
	current = node;
	start = node;
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
	args[count] = NULL;
	current = start;
	count = 0;
	while (current != NULL)
	{
		if (current->special == 1)
			break ;
		args[count] = malloc(ft_strlen(current->cmd) + 1);
		ft_strlcpy(args[count], current->cmd, ft_strlen(current->cmd) + 1);
		current = current->next;
		count++;
	}
	args[count] = NULL;
	print_str_arr(args);
	data->pid = fork();
	if (data->pid == -1)
		return ;
	else if (data->pid == 0)
	{
		if (execve(path, args, env) == -1)
			return ;
	}
	else
	{
		wait(NULL);
	}
	free(path);
	free_2d_str_arr(&args);
}
