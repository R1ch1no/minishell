
#include "../minishell.h"

void	ft_sig_quit(int signal_num)
{
	(void)signal_num;
	g_ex_status = 131;
	ft_putstr_fd("sigquit\n", 2);
	exit(131);
}

void	response(int signal_num)
{
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_response(int signal_num)
{
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		exit(signal_num);
	}
}

void	ft_wait_children(t_data *data)
{
	if (data->children > 0)
	{
		while (data->children > 0)
		{
			waitpid(0, &g_ex_status, 0);
			if (g_ex_status == 2)
			{
				write(1, "\n", 1);
			}
			if (g_ex_status == 131)
			{
				write(2, "Quit (core dumped)\n", 19);
			}
			else
				g_ex_status = WEXITSTATUS(g_ex_status);
			data->children--;
			if (data->red_status == 1)
				g_ex_status = 1;
		}
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
