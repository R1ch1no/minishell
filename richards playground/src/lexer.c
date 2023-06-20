
#include "../minishell.h"

//gets rid of all the whitespaces before and after actual cmd line
void	lexer(t_data *data)
{
	if (data->line_read == NULL)
		return ; //exit
	if (trim_spaces(data) == 1)
		return ;
	init_cmd_line(data);
}

int	trim_spaces(t_data *data)
{
	char	*temp;

	temp = ft_strtrim(data->line_read, " ");
	if (temp == NULL)
		return (cleanse(data), 1); //exit
	free(data->line_read);
	data->line_read = temp;
	return (0);
}