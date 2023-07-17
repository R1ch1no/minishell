/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:05:00 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/30 11:09:19 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_response(int signal_num)
{
	if (signal_num == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		close(STDIN_FILENO);
		unlink(HERE_DOC);
		g_ex_status = CTRL_C;
	}
}

void	heredoc_eof(t_data *data)
{
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("here-document at line X delimited by end-of-file", 2);
	ft_putstr_fd("(wanted `eof')\n", 2),
	close_prev_fd(&data->fd_heredoc);
	clean_heredoc_child(data);
	exit(1);
}

int	heredoc_child(t_data *data, char *limiter)
{
	char	*line;

	g_ex_status = 0;
	signal(SIGINT, heredoc_response);
	while (1)
	{
		line = readline("💩 ");
		if (g_ex_status == CTRL_C)
		{
			clean_heredoc_child(data);
			exit(g_ex_status);
		}
		if (line == NULL)
			heredoc_eof(data);
		if (ft_strcmp_v2(line, limiter) == 0)
			break ;
		check_for_dollar(&line, data);
		write(data->fd_heredoc, line, ft_strlen(line));
		write(data->fd_heredoc, "\n", 1);
		free(line);
	}
	free(line);
	close_prev_fd(&data->fd_heredoc);
	clean_heredoc_child(data);
	exit(0);
}

// O_TRUNC truncates size to 0: empties out file content (if its exist)
int	here_doc(t_data *data, char *limiter)
{
	int	pid;

	close_prev_fd(&data->fd_infile);
	if (!data || limiter == NULL || close_prev_fd(&data->fd_heredoc) == -1)
		return (ERROR);
	data->fd_heredoc = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (data->fd_heredoc == -1)
		return (ERROR);
	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
		heredoc_child(data, limiter);
	signal(SIGINT, SIG_IGN);
	waitpid(0, &g_ex_status, 0);
	g_ex_status = WEXITSTATUS(g_ex_status);
	if (g_ex_status == 256 || g_ex_status == CTRL_C)
		return (close_prev_fd(&data->fd_heredoc), ERROR);
	if (close_prev_fd(&data->fd_heredoc) == -1)
		return (1);
	data->fd_heredoc = open(HERE_DOC, O_RDONLY, 0666);
	if (data->fd_heredoc == -1)
		return (unlink(HERE_DOC), ERROR);
	return (0);
}

int	look_for_heredoc(t_data *data, t_node *head)
{
	t_node	*start;

	if (!head)
		return (-1);
	start = head;
	while (head != NULL)
	{
		if (check_if_token(head, "|") == TRUE)
			return (0);
		if (check_if_token(head, "<<") == TRUE)
		{
			head = head->next;
			if (!head || head == NULL)
				return (0);
			if (here_doc(data, head->cmd) == ERROR)
				return (signal(SIGINT, response), ERROR);
		}
		else
			head = head->next;
	}
	head = start;
	return (0);
}
