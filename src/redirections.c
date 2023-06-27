
#include "../minishell.h"

int	open_infile(char *filename, int *fd)
{
	if (close_prev_fd(fd) == -1)
		return (ERROR);
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		ft_putstr_fd("mini_shit💩: ", 2);
		return (ERROR);
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
		ft_putstr_fd("mini_shit💩: ", 2);
		return (ERROR);
	}
	return (0);
}

int	open_outf_append(char *filename, int *fd)
{
	if (close_prev_fd(fd) == ERROR)
		return (ERROR);
	*fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (*fd == -1)
	{
		ft_putstr_fd("mini shit💩: ", 2);
		return (ERROR);
	}
	return (0);
}

//<< ;D
int	set_redirections(t_node *head, t_data *data)
{
	t_node	*current;
	int		status;

	if (!head || !data)
		return (ERROR);
	current = head;
	status = 0;
	while (current && check_if_token(current, "|") == FALSE && status == 0)
	{
		if (check_if_token(current, "<") == TRUE)
			status = open_infile(current->next->cmd, &data->fd_infile);
		else if (check_if_token(current, "<<") == TRUE)
		{
			status = close_prev_fd(&data->fd_infile);
			data->fd_infile = dup(data->fd_heredoc);
		}
		else if (check_if_token(current, ">") == TRUE)
			status = open_outfile(current->next->cmd, &data->fd_outfile);
		else if (check_if_token(current, ">>") == TRUE)
			status = open_outf_append(current->next->cmd, &data->fd_outfile);
		current = current->next;
	}
	if (status == ERROR)
		g_ex_status = 1;
	return (close_prev_fd(&data->fd_heredoc), status);
}

void	cut_out_redirection(t_node **head)
{
	t_node	*current;

	if (!head)
		return ;
	current = *head;
	while (current && check_if_token(current, "|") == FALSE)
	{
		if (check_if_any_token(current))
		{
			delete_node(current->next, head);
			delete_node(current, head);
			current = *head;
			continue ;
		}
		current = current->next;
	}
}
