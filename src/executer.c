
#include "../minishell.h"

/*
    BIG QUESTION:
    
    should parser only check for grammar
    and executer "prepare" itself str by str 

    EXECUTER:
    if all infiles and maybe heredoc's are opened in before executer the fd is already in data


    Fiona:
    hat sie dann einfach ein 2d array wo alle außer das richtige infile weg ist --> nein,
	alle noch da
*/

//any of the specials in quotes wont work --> "|", "<",
//meaning it will mistake it and tries to pipe

void	executer(t_data *data)
{
	t_node	*current;

	current = data->cmd_line;
	while (current != NULL)
	{
		if (ft_strcmp_node(current, "pwd") == 0)
			ft_pwd(&current);
		else if (ft_strcmp_node(current, "echo") == 0)
		{
			current = current->next;
			ft_echo(&current);
		}
		else if (ft_strcmp_node(current, "cd") == 0)
		{
			current = current->next;
			ft_cd(&current);
		}
		else if (ft_strcmp_node(current, "env") == 0)
			ft_env(data->env_copy, &current);
		else if (ft_strcmp_node(current, "unset") == 0 && current->next)
			ft_unset(data, current->next->cmd, &current);
		if (current != NULL)
			current = current->next;
	}
}

/* void	set_stdin_out(t_data *data)
{
	if
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
			cleanup(data);
	if (dup2(data->fd_out, STDOUT_FILENO) == -1)
		cleanup(data);
}

static int	get_cmd(char *cmd, t_data *data)
{
	int		i;
	char	*env_path;

	i = 0;
	env_path = data->path[i];
	printf("%s\n", env_path);
	while (env_path)
	{
		data->cmd_flags = ft_split(cmd, ' ');
		data->cmd_path = ft_strjoin(env_path, data->cmd_flags[0]);
		if (data->cmd_flags == NULL || data->cmd_path == NULL)
			return (-1);
		if (access(data->cmd_path, X_OK) == -1)
		{
			i++;
			env_path = data->path[i];
			if (env_path == NULL)
				return (-1);
		}
		else
			return (0);
	}
	return (0);
}

void	run_cmd(char *cmd, t_data *data)
{
	if (get_cmd(cmd, data) == -1)
		cleanup(data);
	execve(data->cmd_path, data->cmd_flags, data->env_copy);
	perror("execve");
	cleanup(data);
	exit(1);
} */