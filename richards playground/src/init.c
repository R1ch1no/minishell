
#include "../minishell.h"

void	init_data(t_data *data, char **env)
{
	data->line_read = NULL;
	//must be freed; what happens if environment is empty? easy fix or nah?
	data->env_copy = dup_str_arr(env);
	data->cmd_line = NULL;
	data->fd_infile = -1;
	data->fd_outfile = -1;
	data->fd_heredoc = -1;
	data->fd_pipe[0] = -1;
	data->fd_pipe[1] = -1;
	data->children = 0;
}