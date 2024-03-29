/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:01:04 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/20 16:03:33 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell_core(t_data *data)
{
	lexer(data);
	identify_tokens(data->cmd_line);
	prep_for_executer(&data->cmd_line, data);
	if (loop_each_cmd(data) == ERROR)
		reset_fds(data);
	ft_wait_children(data);
	signal(SIGINT, response);
	data->no = 0;
	ft_clean_cmd(data);
}

//returns TRUE if PIPE is found in cmd_line
int	set_pipe_status(t_node *head)
{
	while (head)
	{
		if (check_if_token(head, "|") == TRUE)
			return (TRUE);
		head = head->next;
	}
	return (FALSE);
}

void	go_next_cmd(t_node **node, t_data *data)
{
	g_ex_status = 1;
	data->red_status = 1;
	perror("In set_redirections");
	delete_til_pipe(&data->cmd_line);
	*node = data->cmd_line;
}

int	loop_each_cmd(t_data *data)
{
	t_node	*current;

	current = data->cmd_line;
	while (current != NULL)
	{
		data->red_status = 0;
		if (look_for_heredoc(data, data->cmd_line) == ERROR)
			return (ERROR);
		if (parser(data->cmd_line) == ERROR)
			return (ERROR);
		if (set_redirections(current, data) == ERROR)
			go_next_cmd(&current, data);
		data->pipe_status = set_pipe_status(current);
		if (data->pipe_status == TRUE)
			open_pipe(data);
		cut_out_redirection(&data->cmd_line);
		if (data->cmd_line && check_if_token(data->cmd_line, "|") == FALSE)
			executer(data);
		if (data->pipe_status == TRUE)
			close_pipe(data);
		close_prev_fd(&data->fd_outfile);
		delete_cmd(&data->cmd_line);
		current = data->cmd_line;
	}
	return (close_prev_fd(&data->fd_infile), unlink(HERE_DOC), 0);
}
