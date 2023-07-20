/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:05:52 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/20 16:04:34 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sig_quit(int signal_num)
{
	(void)signal_num;
	g_ex_status = 131;
	ft_putstr_fd("sigquit\n", 2);
	exit(131);
}

void	response(int signal_num)
{
	if (signal_num == SIGINT)
	{
		g_ex_status = CTRL_C;
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_response(int signal_num)
{
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		exit(SIGINT);
	}
}

void	ft_wait_children(t_data *data)
{
	int	status;
	int	nothing;

	while (data->children > 0)
	{
		if (data->children > 1)
			waitpid(0, &nothing, 0);
		waitpid(data->last_child, &status, 0);
		if (WIFSIGNALED(status) == 1)
		{
			if (status == 2)
			{
				g_ex_status = 130;
				write(1, "\n", 1);
			}
			else if (status == 131)
			{
				g_ex_status = 131;
				write(2, "Quit (core dumped)\n", 19);
			}
		}
		else
			g_ex_status = WEXITSTATUS(status);
		data->children --;
	}
}

//this function sets up incoming signals to be ignored,
//instead of the SIGINT with comes with a promt in new line
void	signal_set_up(t_data *data)
{
	data->sa.sa_handler = SIG_IGN;
	sigemptyset(&data->sa.sa_mask);
	data->sa.sa_flags = 0;
	sigaction(SIGQUIT, &data->sa, NULL);
	signal(SIGINT, response);
}
