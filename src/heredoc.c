
#include "../minishell.h"

//O_TRUNC truncates size to 0: empties out file content (if its exist) 
int	here_doc(t_data *data, char *limiter)
{
	char	*line;

    if (data->fd_heredoc != -1)
    {
        close(data->fd_heredoc);
        data->fd_heredoc = -1;
    }
	data->fd_heredoc = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (data->fd_heredoc == -1)
		return (-1);
    line = NULL;
	while (ft_strcmp_v2(line, limiter) != 0)
	{
		line = readline("💩");
		write(data->fd_heredoc, line, ft_strlen(line));
		free(line);
	}
	close(data->fd_heredoc);
	data->fd_heredoc = open(HERE_DOC, O_RDONLY);
	if (data->fd_heredoc == -1)
		return(unlink(HERE_DOC), -1);
	return (0);
}








