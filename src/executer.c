
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

void	ft_bash(t_data *data, int command)
{
	int		x;
	int		y;
	int		lvl;
	char	*shlvl;
	char	*add;

	x = 0;
	y = -1;
	while (data->env_copy[++y] != NULL)
		if (ft_strcmp_v2_until(data->env_copy[y], "SHLVL=", '=') == 0)
			break ;
	if (data->env_copy[y] == NULL)
		return ;
	while (data->env_copy[y][x] != '=' && data->env_copy[y][x])
		x++;
	if (data->env_copy[y][x] == '=')
		x++;
	lvl = ft_atoi(&data->env_copy[y][x]);
	lvl = lvl + command;
	if (lvl == 0)
	{
		cleanse(data);
		exit(0);
	}
	add = ft_itoa(lvl);
	shlvl = ft_strjoin("SHLVL=", add);
	if (!shlvl || shlvl == NULL)
		return ;
	free(data->env_copy[y]);
	free(add);
	data->env_copy[y] = shlvl;
}

void	executer(t_data *data, char **env)
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
		else if (ft_strcmp_node(current, "export") == 0 && current->next)
			ft_export_a(data, current->next->cmd, &current,
					get_arr_len(data->env_copy) + 1);
		else if (ft_strcmp_node(current, "export") == 0)
			ft_export_na(data->env_copy, &current, get_arr_len(data->env_copy));
		//else
		//	ft_exec(current, data, env);
		(void)env;
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