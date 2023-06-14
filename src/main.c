
#include "../minishell.h"

//pipe[0] = read
//pipe[1] = write

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
	//deleted the run variable, to stop the program, press Ctrl + D
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
		lexer(data); //stopped_here
		identify_tokens(data->cmd_line);
		print_list(data->cmd_line);
		free(data->line_read);
		data->line_read = NULL;
		if (syntaxer(data->cmd_line) == 0)
		{
			prep_for_executer(&data->cmd_line, data); //quotes and dollar
			/*
			//FOLLOWING PART SHOULD BE LOOP
			//look for pipe if needed:
			if (pipe(data->fd_pipe) == -1)
				cleanse(data); //exit()
			data->fd_outfile = data->fd_pipe[1];
			look_for_heredoc(data, data->cmd_line); //only saves an fd but doesnt set fd_infile
 			//parser(); //
			//redirections


			executer(data);
			//in executer:
			//set_redirections(data->cmd_line, data);
			//get 2d array for cmd
			
			
			
			//reset ONLY redirections
			//dup2 pipe[1] into fd_infile
			close_prev_fd(data->fd_outfile);
			close_prev_fd(data->fd_infile);
			data->fd_infile = dup(data->fd_pipe[0]);
			close_prev_fd(data->fd_pipe[0]);
			close_prev_fd(data->fd_pipe[1]);
			*/
			loop_each_cmd(data);
			print_list(data->cmd_line);
		}
		unlink(HERE_DOC);
		//ft_clean_cmd(data);
	}
	//the following block ONLY WRITTEN FOR TESTING PURPOSES
	//free(data.line_read);
	cleanse(data); 
	exit(0);
	return (1);
}

t_node *look_for_pipe(t_node *head)
{
	while (head)
	{
		if (ft_strcmp_v2(head->cmd, "|") == 0 && head->special == 1)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void delete_cmd(t_node *pipe_ptr, t_node **head)
{
	t_node *temp;

	temp = *head;
	while (temp && temp != pipe_ptr)
	{
		delete_node(temp, head);
		temp = *head;
	}
	delete_node(pipe_ptr, head);
}

void loop_each_cmd(t_data *data)
{
	t_node *current;
	t_node *pipe_ptr;

	current = data->cmd_line;
	
	while (current != NULL)
	{
		pipe_ptr = look_for_pipe(current);
		if (pipe_ptr != NULL)
		{
			if (pipe(data->fd_pipe) == -1)
				cleanse(data); //exit()
		}
		data->fd_outfile = data->fd_pipe[1];
		//look_for_heredoc(data, data->cmd_line); //only saves an fd but doesnt set fd_infile
		//parser(); //
		set_redirections(current, data);
		cut_out_redirection(&data->cmd_line);
		executer(data);
		close_prev_fd(&data->fd_outfile);
		close_prev_fd(&data->fd_infile);
		data->fd_infile = dup(data->fd_pipe[0]);
		close_prev_fd(&data->fd_pipe[0]);
		close_prev_fd(&data->fd_pipe[1]);
		delete_cmd(pipe_ptr, &data->cmd_line);
		current = data->cmd_line;
	}
}



// 0 - STDIN
// 1 - STDOUT
// 2 - STDERR
//fd_infile = -1; --> dup(STDIN) --> 3 - STDIN
//fd_outfile = -1;
