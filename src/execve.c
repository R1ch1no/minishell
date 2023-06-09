
#include "../minishell.h"

char	*exec_strjoin(char *str1, char *str2)
{
	char	*jstr;
	int		i;
	int		j;

	if (!str1 || str1 == NULL || !str2 || str2 == NULL)
		return (NULL);
	jstr = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2))
			+ 1);
	if (!jstr || jstr == NULL)
		return (NULL);
	j = 0;
	i = -1;
	while (str1[++i])
		jstr[i] = str1[i];
	while (str2[j])
		jstr[i++] = str2[j++];
	jstr[i] = '\0';
	free(str1);
	return (jstr);
}

int	arg_num(t_node *node)
{
	int		count;
	t_node	*current;
	t_node	*start;

	start = node;
	current = node;
	count = 0;
	while (current != NULL)
	{
		if (current->special == 1)
			break ;
		count++;
		current = current->next;
	}
	current = start;
	return (count);
}

void	fill_args(t_node *node, char **args)
{
	int		count;
	t_node	*current;
	t_node	*start;

	start = node;
	current = node;
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
	current = start;
}

int	forking(t_data *data, char *path, char **env, char **args)
{
	data->pid = fork();
	if (data->pid == -1)
	{
		free(path);
		free_2d_str_arr(&args);
		return (1);
	}
	else if (data->pid == 0)
		execve(path, args, env);
	else
	{
		signal(SIGINT, SIG_IGN);
		wait(NULL);
		free(path);
		free_2d_str_arr(&args);
	}
	return (0);
}

void	ft_exec(t_node *node, t_data *data, char **env)
{
	char		*pre_path;
	static char	*path;
	char		**args;

	if (ft_strcmp_v2_until(node->cmd, "./", '/') == 0)
	{
		path = malloc(ft_strlen(node->cmd) + 1);
		ft_strlcpy(path, node->cmd, ft_strlen(node->cmd) + 1);
	}
	else
	{
		pre_path = malloc(ft_strlen("/usr/bin/") + ft_strlen(node->cmd) + 1);
		if (!pre_path || pre_path == NULL)
			return ;
		ft_strlcpy(pre_path, "/usr/bin/", (ft_strlen("/usr/bin/") + 1));
		path = exec_strjoin(pre_path, node->cmd);
		if (!path || path == NULL)
			return ;
	}
	if (access(path, F_OK) != 0)
	{
		free(path);
		return ;
	}
	args = malloc((arg_num(node) + 1) * sizeof(char *));
	fill_args(node, args);
	forking(data, path, env, args);
	signal_set_up(data);
}
