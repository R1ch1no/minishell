
#include "../minishell.h"

void	ft_sig_quit(int signal_num)
{
	printf("%i\n", signal_num);
	if (signal_num == SIGQUIT)
		exit(1);
}

void	response(int signal_num)
{
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	child_response(int signal_num)
{
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 1);
		rl_redisplay();
		exit(1);
	}
}

void	ft_wait_children(t_data *data)
{
	int	status;

	if (data->children > 0)
	{
		while (data->children > 0)
		{
			waitpid(0, &status, 0);
			data->children--;
		}
		if (status == 1)
			write(1, "\n", 1);
	}
	signal(SIGINT, response);
}

//this function sets up incoming signals to be ignored,
//instead of the SIGINT with comes with a promt in new line
void	signal_set_up(t_data *data)
{
	data->sa.sa_handler = SIG_IGN;
	sigemptyset(&data->sa.sa_mask);
	data->sa.sa_flags = 0;
	sigaction(SIGQUIT, &data->sa, NULL);
	signal(SIGINT, response);
}
