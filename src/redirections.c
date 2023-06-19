
#include "../minishell.h"

int	open_infile(char *filename, int *fd)
{
	if (close_prev_fd(fd) == -1)
		return (-1);
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		ft_putstr_fd("mini_shit💩: Give me a correct filename or directory, you shitface\n", 2);
		return (-1);
	}
	return (0);
}

int	open_outfile(char *filename, int *fd)
{
	if (close_prev_fd(fd) == ERROR)
		return (ERROR);
	*fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (*fd == -1)
	{
		ft_putstr_fd("mini_shit💩: you are shit smth went wrong with open\n", 2);
		return (ERROR);
	}
	return (0);
}

int	open_outfile_in_append(char *filename, int *fd)
{
	if (close_prev_fd(fd) == ERROR)
		return (ERROR);
	*fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (*fd == -1)
	{
		ft_putstr_fd("mini shit💩: you are shit smth went wrong with open\n", 2);
		return (ERROR);
	}
	return (0);
}

int	set_redirections(t_node *head, t_data *data)
{
	t_node	*current;
	int		status;

	if (!head)
		return (-1);
	current = head;
	status = 0;

	while (current && check_if_token(current, "|") == FALSE)
	{
		if (check_if_token(current, "<") == TRUE)
			status = open_infile(current->next->cmd, &data->fd_infile);
		else if (check_if_token(current, "<<") == TRUE)
		{
			status = close_prev_fd(&data->fd_infile);	
			if (status == -1)
				return (status);
			//data->fd_infile = data->fd_heredoc;
			data->fd_infile = dup(data->fd_heredoc); //davor: infile = heredeoc; um keine fds zu verlieren
			close_prev_fd(&data->fd_heredoc);
		}
		else if (check_if_token(current, ">") == TRUE)
			status = open_outfile(current->next->cmd, &data->fd_outfile);
		else if (check_if_token(current, ">>") == TRUE)
			status = open_outfile_in_append(current->next->cmd,
											&data->fd_outfile);
		if (status == -1)
			return (status);
		current = current->next;
	}
	return (0);
}

void	cut_out_redirection(t_node **head)
{
	t_node	*current;

	if (!head)
		return ;
	current = *head;
	while (current && check_if_token(current, "|") == FALSE)
	{
		if (check_if_any_token(current)) //also checks for pipe but loop would never pass pipe
		{
			delete_node(current->next, head);
			delete_node(current, head);
			current = *head;
			continue;
		}
		current = current->next;
	}
}

