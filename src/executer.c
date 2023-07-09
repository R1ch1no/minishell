/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:04:22 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/09 13:58:42 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (is_numeric(&data->env_copy[y][x]) == 1)
		lvl = 0;
	else
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

void	ft_commands(t_node *current, char **env, t_data *data)
{
	if (ft_strcmp_node(current, "pwd") == 0)
		g_ex_status = ft_pwd();
	else if (ft_strcmp_node(current, "echo") == 0)
	{
		current = current->next;
		g_ex_status = ft_echo(&current);
	}
	else if (ft_strcmp_node(current, "env") == 0)
		g_ex_status = ft_env(data->env_copy);
	else if (ft_strcmp_node(current, "export") == 0)
		g_ex_status = ft_export_na(data->env_copy, get_arr_len(data->env_copy));
	else
	{
		close_prev_fd(&data->fd_pipe[0]);
		g_ex_status = ft_exec(current, env, data);
	}
	close_prev_fd(&data->fd_pipe[0]);
	cleanse(data);
	exit(g_ex_status);
}

int	ft_no_child(t_node *current, t_data *data)
{
	char	**args;

	args = malloc((arg_num(current) + 1) * sizeof(char *));
	if (!args || args == NULL)
		return (malloc_error(data), 0);
	fill_args(current, &args);
	if (ft_strcmp_node(current, "unset") == 0 && data->no == 0)
		return (ft_unset(data, &args));
	else if (ft_strcmp_node(current, "exit") == 0 && data->no == 0)
		return (ft_exit(data, &args));
	else if (ft_strcmp_node(current, "cd") == 0 && data->no == 0)
		return (ft_cd(data, &args));
	else if (ft_strcmp_node(current, "export") == 0 && args[1] != NULL
			&& data->no == 0)
	{
		ft_export_a(data, &args);
		free_2d_str_arr(&args);
		return (0);
	}
	if (was_child(current, &args) == 0 && data->no == 1)
		return (0);
	return (free_2d_str_arr(&args), 1);
}

// close_prev_fd(&data->fd_pipe[0]); very important
int	executer(t_data *data)
{
	t_node	*current;

	current = data->cmd_line;
	if (current->cmd[0] == '\0')
		return (g_ex_status = CMD_N_F, ft_putstr_fd("command not found\n", 2),
			0);
	if (ft_no_child(current, data) == 0)
	{
		close_prev_fd(&data->fd_pipe[1]);
		return (data->fd_outfile = -1, 0);
	}
	data->pid = fork();
	if (data->pid == -1)
		return (write(2, "Fork problem!\n", 14) && 0);
	data->children += 1;
	if (data->pid == 0)
	{
		signal(SIGQUIT, ft_sig_quit);
		signal(SIGINT, child_response);
		if (set_stdin_out(data->fd_infile, data->fd_outfile, data))
			exit(1);
		ft_commands(current, data->env_copy, data);
	}
	signal(SIGINT, SIG_IGN);
	return (0);
}
