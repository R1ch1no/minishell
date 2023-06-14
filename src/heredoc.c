
#include "../minishell.h"

// O_TRUNC truncates size to 0: empties out file content (if its exist)
int	here_doc(t_data *data, char *limiter)
{
	printf("HEREDOC function\n");
	char	*line;

	if (limiter == NULL)
		return (0);
	if (close_prev_fd(&data->fd_heredoc))
		return (-1);
	data->fd_heredoc = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (data->fd_heredoc == -1)
		return (-1);
	//line = NULL;
	//while (ft_strcmp_v2(line, limiter) != 0)
	//{
	//	if (line != NULL)
	//		free(line);
	//	line = readline("💩 ");
	//	if (line == NULL)
	//		return (-1);
	//	write(data->fd_heredoc, line, ft_strlen(line));
	//}
	while (1)
	{
		line = readline("💩 ");
		if (line == NULL)
			return (-1);
		if (ft_strcmp_v2(line, limiter) == 0)
			break;
		write(data->fd_heredoc, line, ft_strlen(line));
	}
	close(data->fd_heredoc);
	data->fd_heredoc = open(HERE_DOC, O_RDONLY);
	if (data->fd_heredoc == -1)
		return (unlink(HERE_DOC), -1);
	return (free(line), 0);
}

int look_for_heredoc(t_data *data, t_node *head)
{
	if (!head)
		return (-1);
	printf("Look for HEREDOC\n");
	while (head)
	{
		if ((ft_strcmp_v2(head->cmd, "|") == 0 && head->special == TRUE))
			return (0);
		if (ft_strcmp_v2(head->cmd, "<<") == 0 && head->special == TRUE)
		{
			head = head->next;
			if (here_doc(data, head->cmd) == -1)
				return (-1);
		}
		head = head->next;
	}
	return (0);
}
