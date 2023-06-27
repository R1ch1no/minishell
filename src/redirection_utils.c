
#include "../minishell.h"

int	close_prev_fd(int *fd)
{
	if (*fd != -1)
	{
		if (close(*fd) == -1)
		{
			printf("FD: %d\n", *fd);
			return (perror("mini_shit💩: something went wrong with close\n"),
				-1);
		}
		*fd = -1;
	}
	return (0);
}

int	reset_fds(t_data *data)
{
	if (close_prev_fd(&data->fd_infile) == -1)
		return (ERROR);
	if (close_prev_fd(&data->fd_outfile) == -1)
		return (ERROR);
	if (close_prev_fd(&data->fd_heredoc) == -1)
		return (ERROR);
	if (close_prev_fd(&data->fd_pipe[0]) == -1)
		return (ERROR);
	if (close_prev_fd(&data->fd_pipe[1]) == -1)
		return (ERROR);
	return (0);
}

int	open_pipe(t_data *data)
{
	if (pipe(data->fd_pipe) == -1)
		cleanse(data);
	if (data->fd_outfile == -1)
		data->fd_outfile = data->fd_pipe[1];
	else
		close_prev_fd(&data->fd_pipe[1]);
	return (0);
}

int	close_pipe(t_data *data)
{
	close_prev_fd(&data->fd_infile);
	if (data->fd_pipe[1] == data->fd_outfile)
		data->fd_pipe[1] = -1;
	data->fd_infile = dup(data->fd_pipe[0]);
	close_prev_fd(&data->fd_pipe[0]);
	return (0);
}
