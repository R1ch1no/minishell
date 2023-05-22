/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:15:39 by qtran             #+#    #+#             */
/*   Updated: 2023/05/22 16:38:52 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_2d_arr_len(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		s1_len;
	int		i;

	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	dest = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**dup_str_arr(char **ori)
{
	int		i;
	char	**copy;

	i = 0;
	if (ori == NULL || ori[0] == NULL)
		return (NULL);
	copy = malloc((get_2d_arr_len((void **)ori) + 1) * sizeof(char *));
	if (copy == NULL)
	{
		perror("minishell malloc");
		exit(1);
	}
	while (ori[i])
	{
		copy[i] = ft_strdup(ori[i]);
		if (copy[i] == NULL)
		{
			perror("minishell malloc");
			free_2d_str_until(copy, i);
			exit(1);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
