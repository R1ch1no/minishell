
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

int	ft_getlvl(t_data *data, int y)
{
	int	lvl;
	int	x;

	x = 0;
	while (data->env_copy[++y] != NULL)
		if (ft_strcmp_v2_until(data->env_copy[y], "SHLVL=", '=') == 0)
			break ;
	if (data->env_copy[y] == NULL)
		return (-1);
	while (data->env_copy[y][x] != '=' && data->env_copy[y][x])
		x++;
	if (data->env_copy[y][x] == '=')
		x++;
	lvl = ft_atoi(&data->env_copy[y][x]);
	if (lvl <= 0)
		return (0);
	return (lvl);
}

void	ft_bash(t_data *data, int command)
{
	int		y;
	int		lvl;
	char	*shlvl;
	char	*add;

	y = -1;
	lvl = ft_getlvl(data, y) + command;
	if (lvl == -1)
		return ;
	if (lvl == 0)
	{
		cleanse(data);
		exit(0);
	}
	add = ft_itoa(lvl);
	shlvl = ft_strjoin("SHLVL=", add);
	if (!shlvl || shlvl == NULL)
		return ;
	while (data->env_copy[++y] != NULL)
		if (ft_strcmp_v2_until(data->env_copy[y], "SHLVL=", '=') == 0)
			break ;
	free(data->env_copy[y]);
	free(add);
	data->env_copy[y] = shlvl;
}

int	ft_commands(t_node *current, char **env, t_data *data)
{
	if (ft_strcmp_node(current, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp_node(current, "echo") == 0)
	{
		current = current->next;
		return (ft_echo(&current));
	}
	else if (ft_strcmp_node(current, "cd") == 0)
	{
		current = current->next;
		return (ft_cd(&current));
	}
	else if (ft_strcmp_node(current, "env") == 0)
		return (ft_env(data->env_copy));
	else if (ft_strcmp_node(current, "export") == 0)
		return (ft_export_na(data->env_copy, get_arr_len(data->env_copy)));
	else
		return (ft_exec(current, env));
	return (0);
}

int	ft_no_child(t_node *current, t_data *data)
{
	if (ft_strcmp_node(current, "unset") == 0 && current->next)
		return (ft_unset(data, current->next->cmd));
	else if (ft_strcmp_node(current, "export") == 0 && current->next)
		return (ft_export_a(data, current->next->cmd, &current,
				get_arr_len(data->env_copy) + 1));
	else
		return (1);
}

int	executer(t_data *data)
{
	t_node	*current;

	current = data->cmd_line;
	print_list(data->cmd_line);
	if (ft_no_child(current, data) == 0)
		return (0);
	data->pid = fork();
	if (data->pid == -1)
		return (write(2, "Fork problem!\n", 14) && 0);
	data->children += 1;
	if (data->pid == 0)
	{
		close_prev_fd(&data->fd_pipe[0]);
		if (set_stdin_out(data->fd_infile, data->fd_outfile, data))
			exit(0);
		if (ft_commands(current, data->env_copy, data) == 1)
			printf("command not found : %s", current->cmd);
		return (0);
	}
	else
		signal(SIGINT, SIG_IGN);
	return (0);
}
