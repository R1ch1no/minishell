
#include "../minishell.h"

void	lexer(t_data *data)
{
	if (data->line_read == NULL)
		return ; //exit
	//gets rid of all the whitespaces before and after actual cmd line
	if (trim_spaces(data) == 1)
		return ;
	data->cmd_line = malloc(sizeof(char *) * (count_tokens_v2(data->line_read)
				+ 1));
	if (data->cmd_line == NULL)
		return (perror("minishell malloc"), cleanse(data));
	init_cmd_line(data);
}

int	trim_spaces(t_data *data)
{
	char	*temp;

	temp = ft_strtrim(data->line_read, " ");
	if (temp == NULL)
		return (cleanse(data), 1);
	free(data->line_read);
	data->line_read = temp;
	//printf("trimmed spaces succesfully!\n");
	//printf("This is in line_read: (%s)\n", data->line_read);//
	return (0);
}
