
#include "../minishell.h"

int close_prev_fd(int *fd)
{
    if (*fd != -1)
    {
        if (close(*fd) == -1)
            return (perror("mini_shit💩: you are shit smth went wrong with close\n"), -1);
        *fd = -1;
    }
    return (0);
}

int reset_in_out_stream(t_data *data)
{
    if (close_prev_fd(&data->fd_infile) == -1)
        return (-1);
    if (close_prev_fd(&data->fd_outfile) == -1)
        return (-1);
    if (close_prev_fd(&data->fd_heredoc) == -1)
        return (-1);
    return (0);
}
