
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
	else if (ft_strcmp_node(current, "unset") == 0 && current->next)
		return (ft_unset(data, current->next->cmd));
	else if (ft_strcmp_node(current, "export") == 0 && current->next)
		return (ft_export_a(data, current->next->cmd, &current,
				get_arr_len(data->env_copy) + 1));
	else if (ft_strcmp_node(current, "export") == 0)
		return (ft_export_na(data->env_copy, get_arr_len(data->env_copy)));
	else
		return (ft_exec(current, env));
	return (0);
}

void	executer(t_data *data, char **env)
{
	t_node	*current;

	current = data->cmd_line;
	data->pid = fork();
	if (data->pid == -1)
	{
		write(2, "Fork problem!\n", 14);
		return ;
	}
	else if (data->pid == 0)
	{
		ft_commands(current, env, data);
		/*printf("command not found : %s", current->cmd); */
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		wait(NULL);
		signal_set_up(data);
	}
}
