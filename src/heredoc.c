
#include "../minishell.h"

void	heredoc_response(int signal_num)
{
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_redisplay();
		close_prev_fd(&g_quit_heredoc);
		g_quit_heredoc = TRUE;
		exit(1);
	}
}

void	heredoc_eof(t_data *data)
{
	printf("warning: ");
	printf("here-document at line X delimited by end-of-file (wanted `eof')\n");
	ft_clean_cmd(data);
	exit(0);
}

// O_TRUNC truncates size to 0: empties out file content (if its exist)
int	here_doc(t_data *data, char *limiter)
{
	char	*line;
	int		pid;
	int		status;

	if (limiter == NULL || close_prev_fd(&data->fd_heredoc) == -1)
		return (ERROR);
	data->fd_heredoc = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (data->fd_heredoc == -1)
		return (ERROR);
	g_quit_heredoc = data->fd_heredoc;
	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		signal(SIGINT, heredoc_response);
		while (1)
		{
			line = readline("💩 ");
			if (line == NULL)
				return (heredoc_eof(data), ERROR);
			if (ft_strcmp_v2(line, limiter) == 0)
				break ;
			write(data->fd_heredoc, line, ft_strlen(line));
			write(data->fd_heredoc, "\n", 1);
			free(line);
		}
		free(line); 
		close_prev_fd(&data->fd_heredoc);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(0, &status, 0);
	if (status == 256)
		g_quit_heredoc = TRUE;
	if (close_prev_fd(&data->fd_heredoc) == -1)
		return (1);
	data->fd_heredoc = open(HERE_DOC, O_RDONLY, 0666);
	if (data->fd_heredoc == -1)
		return (unlink(HERE_DOC), ERROR);
	return (0);
}

int	stop_heredoc(t_data *data)
{
	close_prev_fd(&data->fd_heredoc);
	unlink(HERE_DOC);
	return (ERROR);
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
			{
				if (g_quit_heredoc == TRUE)
				{
					//write(STDIN_FILENO, "\n", 1);
					rl_on_new_line();
					rl_redisplay();
					g_quit_heredoc = FALSE;
				}
				return (signal(SIGINT, response), ERROR);
			}
		}
		else
			head = head->next;
	}
	head = start;
	return (0);
}
