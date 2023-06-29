/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:05:56 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/29 18:05:57 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//libft alikes
char	*ft_str_many_chr(char *str, char *set)
{
	int	i;
	int	j;

	if (!str || !set)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (set[j])
		{
			if (str[i] == set[j])
				return (&str[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (&str[i]);
}

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	char	*str;
	char	*temp;

	if (!s1 || !s2 || !s3)
		return (NULL);
	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	str = ft_strjoin(temp, s3);
	free(temp);
	if (!str)
		return (NULL);
	return (str);
}

void	four_free(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
}

int	len_2d_str_arr(char **str)
{
	int	y;

	y = 0;
	while (str[y] != NULL)
		y++;
	return (y);
}

int	ft_find(t_data *data, char *search)
{
	int	x;
	int	y;

	if (search == NULL)
		return (0);
	y = -1;
	while (data->env_copy[++y])
	{
		x = 0;
		while (data->env_copy[y][x] && search[x])
		{
			if (search[x] == data->env_copy[y][x] && search[x + 1] == '\0')
				return (1);
			if (search[x] != data->env_copy[y][x])
				break ;
			x++;
		}
	}
	return (0);
}
