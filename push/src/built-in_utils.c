/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:00:51 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/09 13:44:59 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_flag(char *str)
{
	int	i;

	i = -1;
	if (str[0] != '-')
		return (0);
	if (str[0] == '-')
		i += 1;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

void	echo_print(t_node **node, int n)
{
	int	i;

	while ((*node) != NULL)
	{
		i = -1;
		if ((*node)->special == 1)
			return ;
		while ((*node)->cmd[++i])
		{
			if (n == 1 && (*node)->cmd[i + 1] == '\0'
				&& (*node)->cmd[i] == '\n')
				break ;
			write(1, &(*node)->cmd[i], 1);
		}
		(*node) = (*node)->next;
		if ((*node) != NULL)
			if ((*node)->special != 1)
				write(1, " ", 1);
	}
}

int	set_stdin_out(int fd_in, int fd_out, t_data *data)
{
	if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			close_prev_fd(&data->fd_pipe[0]);
			cleanse(data);
			return (1);
		}
		close(fd_in);
	}
	if (fd_out != -1)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			close_prev_fd(&data->fd_pipe[1]);
			cleanse(data);
			return (1);
		}
		close(fd_out);
	}
	return (0);
}

void	ft_problem(t_data *data, char **new_env, int z)
{
	ft_putstr_fd("mini_shell : malloc error\n", 2);
	free_2d_str_until(new_env, z);
	cleanse(data);
}

int	is_numeric(char *argv)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if ((argv[i] < '0' || argv[i] > '9'))
			return (1);
	}
	return (0);
}
