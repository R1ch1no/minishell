
#include "../minishell.h"

//cleanse all shit but doesnt exit
void	cleanse(t_data *data)
{
	if (!data)
		return ;
	if (data->line_read != NULL)
	{
		free(data->line_read);
		data->line_read = NULL;
	}
	rl_clear_history();
	free_2d_str_arr(&data->env_copy);
	ft_clean_cmd(data);
	free(data);
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
