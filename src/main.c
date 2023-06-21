
#include "../minishell.h"

//pipe[0] = read
//pipe[1] = write

int g_quit_heredoc = FALSE;

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc != 1 || argv[0] == NULL)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Data can't be allocated!\n", 25) && 0);
	init_data(data, env);
	signal_set_up(data);
	ft_bash(data, 1);
	while (1)
	{
		data->line_read = readline("\e[0;93m⮡\e[0;91m mini_hell \e[0m");
		if (data->line_read == NULL)
		{
			printf("exit\n");
			cleanse(data);
			exit(0); //exit && free (cleanup exits for now)
		}
		if (data->line_read[0] == '\0') //empty string
		{
			free(data->line_read);
			continue ;
		}
		if (data->line_read)
			//checks if str is not NULL and not empty
			add_history(data->line_read);
		lexer(data);
		free(data->line_read);
		data->line_read = NULL;
		identify_tokens(data->cmd_line);
		//print_list(data->cmd_line);
		if (syntaxer(data->cmd_line) == 0)
		{
			prep_for_executer(&data->cmd_line, data); //quotes and dollar
			loop_each_cmd(data);
			ft_wait_children(data);
			ft_clean_cmd(data);
			//print_list(data->cmd_line);
		}
		//unlink(HERE_DOC);
	}
	return (1);
}

int set_pipe_status(t_node *head)
{
	while (head)
	{
		if (ft_strcmp_v2(head->cmd, "|") == 0 && head->special == 1)
			return (TRUE);
		head = head->next;
	}
	return (FALSE);
}

void	delete_cmd(t_node **head)
{
	t_node	*temp;

	if (*head == NULL)
		return ;
	temp = *head;
	while (temp && !(ft_strcmp_v2(temp->cmd, "|") == 0 && temp->special == 1))
	{
		delete_node(temp, head);
		temp = *head;
	}
	delete_node(temp, head);
}

void	loop_each_cmd(t_data *data)
{
	t_node	*current;
	int pipe_status;

	current = data->cmd_line;
	while (current != NULL)
	{
		look_for_heredoc(data, data->cmd_line);
		if (g_quit_heredoc == TRUE)
		{
			g_quit_heredoc = FALSE;
			break;
		}
		//signal(SIGINT, response);
		if (parser(data->cmd_line) == ERROR)
		{
			close_prev_fd(&data->fd_heredoc);
			break;
		}	
		if (set_redirections(current, data) == ERROR)
		{
			printf("Broke out cuz set_redirections\n");
			break;
		}
		pipe_status = set_pipe_status(current);
		if (pipe_status == TRUE)
			open_pipe(data);
		cut_out_redirection(&data->cmd_line);
		//printf("No redirections until first pipe at least\n");
		//print_list(data->cmd_line);
		if (data->cmd_line && check_if_token(data->cmd_line, "|") == FALSE)
		{
			//printf("cmd: %s\n", data->cmd_line->cmd);
			executer(data);
		}
   		close_prev_fd(&data->fd_infile);
		//reset_in_out_stream(data);
		if (pipe_status == TRUE)
			close_pipe(data);
		close_prev_fd(&data->fd_outfile);
		delete_cmd(&data->cmd_line); //including pipe
		//print_list(data->cmd_line);
		current = data->cmd_line;
	}
    //close_prev_fd(&data->fd_infile);
}

// 0 - STDIN
// 1 - STDOUT
// 2 - STDERR
//fd_in: STDIN
//fd_out: STDOUT

//fd_infile = -1; --> dup(STDIN) --> 3 - STDIN
//fd_outfile = -1;
