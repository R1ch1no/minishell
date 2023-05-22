/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:25:07 by qtran             #+#    #+#             */
/*   Updated: 2023/05/22 16:40:09 by rkurnava         ###   ########.fr       */
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

void	print_str_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
	{
		printf("arr == NULL");
		return ;
	}
	while (arr[i])
	{
		printf("%s#\n", arr[i]);
		i++;
	}
	printf("%s#\n", arr[i]); //prints the NULL terminator
}
