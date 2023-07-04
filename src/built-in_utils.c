/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:00:51 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/29 18:03:21 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
