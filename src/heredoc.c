
#include "../minishell.h"

void	heredoc_response(int signal_num)
{
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		close(0);
		//close_prev_fd(&g_quit_heredoc);
		g_quit_heredoc = TRUE;
		//exit(1);
	}
}

void	heredoc_eof(t_data *data)
{
	(void)data;
	printf("warning: ");
	printf("here-document at line X delimited by end-of-file (wanted `eof')\n");
	//close_prev_fd(&data->fd_heredoc); //
	//ft_clean_cmd(data);               //
	//exit(0);
}

int	heredoc_child(t_data *data, char *limiter)
{
	char	*line;
	int		i;

	g_quit_heredoc = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_response);
	while (1)
	{
		i = 0;
		line = readline("💩 ");
		if (g_quit_heredoc == TRUE)
			break ;
		if (line == NULL)
			return (heredoc_eof(data), ERROR);
		if (ft_strcmp_v2(line, limiter) == 0)
			break ;
		while (line[i])
		{
			if (line[i] == '$')
				i += subout_dollar(&line, i, FALSE, data);
			else
				i++;
		}
		write(data->fd_heredoc, line, ft_strlen(line));
		write(data->fd_heredoc, "\n", 1);
		free(line);
	}
	free(line);
	return (0);
	//exit(0);
}

// O_TRUNC truncates size to 0: empties out file content (if its exist)
int	here_doc(t_data *data, char *limiter)
{
	//int		pid;
	//int		status;

	printf("HERE DAWG\n");
	if (!data || limiter == NULL || close_prev_fd(&data->fd_heredoc) == -1)
		return (ERROR);
	data->fd_heredoc = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (data->fd_heredoc == -1)
		return (ERROR);
	//g_quit_heredoc = data->fd_heredoc;
	//pid = fork();
	//if (pid == -1)
	//	return (ERROR);
	//if (pid == 0)
	heredoc_child(data, limiter);
	if (g_quit_heredoc == TRUE)
	{
		dup2(g_quit_heredoc, 0);
		//rl_on_new_line();
		//rl_redisplay();
	}
	signal(SIGINT, SIG_IGN);
	//waitpid(0, &status, 0);
	//if (status == 256) //dont know exactly what thats for, if needed could be saved in global
	//	return (close_prev_fd(&data->fd_heredoc), ERROR);
	if (close_prev_fd(&data->fd_heredoc) == ERROR)
		return (ERROR);
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
				return (ERROR);
			if (here_doc(data, head->cmd) == ERROR)
				return (ERROR);
		}
		else
			head = head->next;
	}
	head = start;
	return (0);
}
