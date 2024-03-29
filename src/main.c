/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:05:22 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/20 15:57:31 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_ex_status = 0;

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc != 1 || argv[0] == NULL || env == NULL)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data || data == NULL)
		return (write(2, "Data can't be allocated!\n", 25) && 0);
	init_data(data, env);
	ft_bash(data, 1);
	while (1)
	{
		data->line_read = readline(PROMPT);
		if (data->line_read == NULL)
			eof(data);
		else if (data->line_read[0] == '\0')
		{
			free(data->line_read);
			continue ;
		}
		else
			add_history(data->line_read);
		minishell_core(data);
	}
	return (1);
}

void	eof(t_data *data)
{
	printf("exit\n");
	cleanse(data);
	exit(0);
}

void	init_data(t_data *data, char **env)
{
	data->line_read = NULL;
	data->env_copy = dup_str_arr(env);
	if (data->env_copy == NULL)
	{
		ft_putstr_fd("You are so funny Elijah :D\n", 2);
		free(data);
		exit(1);
	}
	data->cmd_line = NULL;
	data->fd_infile = -1;
	data->fd_outfile = -1;
	data->fd_heredoc = -1;
	data->fd_pipe[0] = -1;
	data->fd_pipe[1] = -1;
	data->children = 0;
	data->no = 0;
	data->red_status = 0;
	data->problem = 0;
	data->old_pwd = -1;
	data->pwd = -1;
	data->last_child = -1;
	signal_set_up(data);
}
