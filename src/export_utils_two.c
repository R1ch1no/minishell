/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:25:06 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/14 12:10:29 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_numlen(long long num)
{
	int i;

	i = 0;
	while (num)
	{
		num = num / 10;
		i ++;
	}
	return (i);
}

int	ex_cmp(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if ((*s1 == '=' && *s2 == '\0'))
		return (1);
	return (0);
}

int	empty_var_exist(t_data *data, char *args)
{
	int	x;

	x = -1;
	if (!args)
		return (0);
	while (data->env_copy[++x])
		if (ex_cmp(data->env_copy[x], args) == 1)
			return (1);
	return (0);
}
