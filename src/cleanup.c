/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:00:58 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/14 11:54:59 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	malloc_error(t_data *data)
{
	ft_putstr_fd("mini_shell : malloc error\n", 2);
	cleanse(data);
	exit(1);
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

void	free_2d_str_until(char **arr, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
