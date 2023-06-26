
#include "../minishell.h"

void	heredoc_response(int signal_num)
{
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		ex_status = CTRL_C;
	}
}

void	heredoc_eof(t_data *data)
{
	printf("warning: ");
	printf("here-document at line X delimited by end-of-file (wanted `eof')\n");
	close_prev_fd(&data->fd_heredoc);
	clean_heredoc_child(data);
	exit(0);
}

int	heredoc_child(t_data *data, char *limiter)
{
	char	*line;

	signal(SIGINT, heredoc_response);
	while (1)
	{
		line = readline("💩 ");
		if (ex_status == CTRL_C)
		{
			clean_heredoc_child(data);
			exit(ex_status);
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
	int		pid;
	//int		status;

	printf("HERE DAWG\n");
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
	//what does SIG_IGN do? 
	//is it for minishell in minishell in .. if smth happens in one heredoc so it doesnt fuck the others?
	waitpid(0, &ex_status, 0);
	ex_status = WEXITSTATUS(ex_status);
	if (ex_status == 256)
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
				return (ERROR);
			if (here_doc(data, head->cmd) == ERROR)
				return (signal(SIGINT, response), ERROR);
		}
		else
			head = head->next;
	}
	head = start;
	return (0);
}
