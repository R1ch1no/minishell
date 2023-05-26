
#include "../minishell.h"

void	cleanse(t_data *data)
{
	if (data->line_read != NULL)
	{
		free(data->line_read);
		data->line_read = NULL;
	}
	free_2d_str_arr(&data->env_copy);
	free_2d_str_arr(&data->cmd_line);
	printf("finished cleanup\n");
}

void	free_2d_str_arr(char ***arr)
{
	int	i;

	i = 0;
	if (*arr == NULL)
		return ;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}
/* 
void	free_2d_str_arr_v2(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
} */


void	free_2d_str_until(char **arr, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}
