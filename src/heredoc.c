
#include "../minishell.h"

// O_TRUNC truncates size to 0: empties out file content (if its exist)
int	here_doc(t_data *data, char *limiter)
{
	char	*line;

	//printf("HEREDOC function\n");
	if (limiter == NULL)
		return (ERROR);
	if (close_prev_fd(&data->fd_heredoc) == -1)
		return (ERROR);
	data->fd_heredoc = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (data->fd_heredoc == -1)
		return (ERROR);
	while (1)
	{
		line = readline("💩 ");
		if (line == NULL)
			return (ERROR);
		if (ft_strcmp_v2(line, limiter) == 0)
			break ;
		write(data->fd_heredoc, line, ft_strlen(line));
		write(data->fd_heredoc, "\n", 1);
	}
	close_prev_fd(&data->fd_heredoc);
	data->fd_heredoc = open(HERE_DOC, O_RDONLY, 0666);
	if (data->fd_heredoc == -1)
		return (unlink(HERE_DOC), ERROR);
	return (free(line), 0);
}

int	look_for_heredoc(t_data *data, t_node *head)
{
	t_node	*start;

	if (!head)
		return (-1);
	start = head;
	printf("Look for HEREDOC\n");
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
