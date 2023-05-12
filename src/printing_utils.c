/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:25:07 by qtran             #+#    #+#             */
/*   Updated: 2023/05/07 15:00:47 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_int_arr(int *arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("arr[%d]: %d\n", i, arr[i]);
		i++;
	}
}

void print_str_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        printf("%s#\n", arr[i]);
        i++;
    }
    printf("%s#\n", arr[i]); //prints the NULL terminator
}
