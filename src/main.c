
#include "../minishell.h"

/*
	//pipe[0] = read
	//pipe[1] = write

After line_read:
- its being checked for eof
- empty string (instant carriage return by user)
*/
int		g_quit_heredoc = FALSE;

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc != 1 || argv[0] == NULL)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Data can't be allocated!\n", 25) && 0);
	init_data(data, env);
	ft_bash(data, 1);
	while (1)
	{
		data->line_read = readline(PROMPT);
		if (data->line_read == NULL)
			eof(data);
		else if (data->line_read[0] == '\0')
		{
			free(data->line_read);
			continue ;
		}
		else
			add_history(data->line_read);
		minishell_core(data);
	}
	return (1);
}

void	eof(t_data *data)
{
	//ft_putstr_fd("exit\n", STDERR_FILENO);
	cleanse(data);
	exit(0); //exit && free (cleanup exits for now)
}

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
	data->status = 0;
	data->problem = 0;
	signal_set_up(data);
}
