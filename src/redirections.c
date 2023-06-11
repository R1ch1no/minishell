
#include "../minishell.h"

int close_prev_fd(int *fd)
{
    if (*fd != -1)
    {
        if (close(*fd) == -1)
            return (perror("mini shit💩: you are shit smth went wrong with close"), -1);
        *fd = -1;
    }
    return (0);
}


int open_infile(char *filename, int *old_fd)
{
    int fd;
    
    close_prev_fd(old_fd);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        ft_putstr_fd("mini shit💩: Give me a correct filename or directory, you shitface", 2);
    return (fd);
}

int open_outfile(char *filename, int *old_fd)
{
    int fd;
    
    close_prev_fd(old_fd);
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd == -1)
        ft_putstr_fd("mini shit💩: you are shit smth went wrong with open", 2);
    return (fd);
}

int open_outfile_in_append(char *filename, int *old_fd)
{
    int fd;
    
    close_prev_fd(old_fd);
    fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666);
    if (fd == -1)
        ft_putstr_fd("mini shit💩: you are shit smth went wrong with open", 2);
    return (fd);
}


int set_redirections(t_node **head, t_data *data)
{
    t_node *current;

	if (!head)
		return (NULL);
	
    current = *head;
    while (current && current->cmd != "|" && current->special != TRUE)
	{
        if (current->cmd == "<" && current->special == TRUE)
            data->fd_infile = open_infile(current->next->cmd, &data->fd_infile);
        else if (current->cmd == ">" && current->special == TRUE)
            data->fd_outfile = open_outfile(current->next->cmd, &data->fd_outfile);
        else if (current->cmd == ">>" && current->special == TRUE)
            data->fd_outfile = open_outfile_in_append(current->next->cmd, &data->fd_outfile);
		current = current->next;
	}
	return (0);
}

void cut_out_redirection(t_node **head)
{
    t_node *current;

    if (!head)
    	return ;
    current = *head;
    while (current && current->cmd != "|" && current->special != TRUE)
    {
        if (current->special == TRUE 
            && (current->cmd == "<" || current->cmd == ">" || current->cmd == ">>"))
        {
            delete_node(current->next, head);
            delete_node(current, head);
            current = *head;
        }
        else
		    current = current->next;
    }
}
