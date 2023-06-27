
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

//counts homw many arguments are in the list till special character
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

//fill the 2d array with arguments to be passted to executable
void	fill_args(t_node *node, char ***args)
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
		(*args)[count] = (char *)malloc(ft_strlen(current->cmd) + 1);
		ft_strlcpy((*args)[count], current->cmd, ft_strlen(current->cmd) + 1);
		current = current->next;
		count++;
	}
	(*args)[count] = NULL;
	current = start;
}

//responsible for creating child processes for the execve
int	execute_cmd(char *path, char **env, char **args)
{
	if (execve(path, args, env) == -1)
		g_ex_status = 1;
	free(path);
	free_2d_str_arr(&args);
	return (0);
}

//execve function
int	ft_exec(t_node *node, char **env)
{
	char	*path;
	char	**args;
	int		start;

	path = NULL;
	args = NULL;
	start = before_start(node);
	if (start != 0)
		return (start);
	if (ft_strcmp_v2_until(node->cmd, "./", '/') == 0)
	{
		g_ex_status = ft_exec_here(&path, node, &args);
		if (g_ex_status != 0)
			return (g_ex_status);
	}
	else
	{
		g_ex_status = ft_exec_path(env, &path, node, &args);
		if (g_ex_status != 0)
			return (g_ex_status);
	}
	fill_args(node, &args);
	return (execute_cmd(path, env, args) && 0);
}
