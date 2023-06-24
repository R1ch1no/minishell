
#include "../minishell.h"




void minishell_core(t_data *data)
{
	lexer(data); //line_read is freed in lexer
	identify_tokens(data->cmd_line);
	prep_for_executer(&data->cmd_line, data); //quotes and dollar
	if (loop_each_cmd(data) == ERROR)
		reset_fds(data);
	ft_wait_children(data);
	ft_clean_cmd(data);
}
//returns TRUE if PIPE is found in cmd_line
int set_pipe_status(t_node *head)
{
	while (head)
	{
		if (check_if_token(head, "|") == TRUE)
			return (TRUE);
		head = head->next;
	}
	return (FALSE);
}

//deletes until pipe(inclusive) or null
void	delete_cmd(t_node **head)
{
	t_node	*temp;

	if (*head == NULL)
		return ;
	temp = *head;
	while (temp && check_if_token(temp, "|") == FALSE)
	{
		delete_node(temp, head);
		temp = *head;
	}
	delete_node(temp, head);
}

int	loop_each_cmd(t_data *data)
{
	t_node	*current;
	int pipe_status;

	current = data->cmd_line;
	while (current != NULL)
	{
		if (look_for_heredoc(data, data->cmd_line) == ERROR)//evtl parser und heredoc tauschen, bash DUMM
			return (ERROR);
		if (parser(data->cmd_line) == ERROR)
			return (ERROR);
		if (set_redirections(current, data) == ERROR)
			return (perror("In set_redirections") , ERROR);
		pipe_status = set_pipe_status(current);
		if (pipe_status == TRUE)
			open_pipe(data);
		cut_out_redirection(&data->cmd_line);
		if (data->cmd_line && check_if_token(data->cmd_line, "|") == FALSE)
		{
			executer(data);
		}
		if (pipe_status == TRUE)
			close_pipe(data);
		close_prev_fd(&data->fd_outfile);
		delete_cmd(&data->cmd_line); //including pipe
		current = data->cmd_line;
	}
	return (close_prev_fd(&data->fd_infile), unlink(HERE_DOC), 0);
}


