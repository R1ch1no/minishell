
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

void	ft_exec(t_node *node, t_data *data, char **env)
{
	int			count;
	char		*pre_path;
	static char	*path;
	char		**args;
	t_node		*current;

	current = node;
	count = 0;
	pre_path = malloc(ft_strlen("/usr/bin/") + ft_strlen(node->cmd) + 1);
	if (!pre_path || pre_path == NULL)
		return ;
	ft_strlcpy(pre_path, "/usr/bin/", (ft_strlen("/usr/bin/") + 1));
	path = exec_strjoin(pre_path, node->cmd);
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
	data->pid = fork();
	if (data->pid == -1)
	{
		free(path);
		free_2d_str_arr(&args);
		return ;
	}
	else if (data->pid == 0)
		execve(path, args, env);
	else
		wait(NULL);
	free(path);
	free_2d_str_arr(&args);
}
