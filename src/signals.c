/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:22:02 by rkurnava          #+#    #+#             */
/*   Updated: 2023/05/25 15:20:16 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	response(int signal_num)
{
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	signal_set_up(t_data *data)
{
	data->sa.sa_handler = SIG_IGN;
	sigemptyset(&data->sa.sa_mask);
	data->sa.sa_flags = 0;
	sigaction(SIGQUIT, &data->sa, NULL);
	signal(SIGINT, response);
}
