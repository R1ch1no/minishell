/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:05:02 by qtran             #+#    #+#             */
/*   Updated: 2023/05/07 14:58:55 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void cleanup(t_data *data)
{
    if (data->line_read != NULL)
    {
       free(data->line_read);
       data->line_read = NULL;
    }
    if (data->env_copy != NULL)
        free_2d_str_arr(data->env_copy);
    printf("finished cleanup\n");
}

void free_2d_str_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        arr[i] = NULL;
        i++;
    }
    free(arr);
    arr = NULL;
}

void free_2d_str_until(char **arr, int end)
{
	int i;

	i = 0;	
	while (i < end)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}