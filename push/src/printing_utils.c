/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:05:34 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/29 18:05:35 by rkurnava         ###   ########.fr       */
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
	printf("%s#\n", arr[i]);
}
