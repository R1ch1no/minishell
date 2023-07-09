/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:04:52 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/29 18:04:53 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp_node(t_node *node, char *s2)
{
	char	*s1;

	if (node != NULL)
		s1 = node->cmd;
	else
		return (9999);
	if (s1 == NULL || s2 == NULL)
		return (9999);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((int)(unsigned char)(*s1) - (int)(unsigned char)(*s2));
}

int	ft_strcmp_v2(char *s1, char *s2)
{
	if (!s1 || s1 == NULL || !s2 || s2 == NULL)
		return (9999);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((int)(unsigned char)(*s1) - (int)(unsigned char)(*s2));
}

//compare two string, if they match unitl and including the character specified
//it returns 0. If somebody says export += it returns -9999 otherwise returns
//difference of s1 and s2 if they dont match at all
int	ft_strcmp_v2_until(char *s1, char *s2, char c)
{
	if (s1 == NULL || s2 == NULL)
		return (9999);
	while (*s1 && *s2 && *s1 == *s2)
	{
		if (*s1 == c && *s2 == c)
			return (0);
		s1++;
		s2++;
	}
	if (*s1 == '=' && *s2 == '-')
		ft_putstr_fd("not a valid identifier", 2);
	if (*s1 == '=' && *s2 == '+')
		return (-9999);
	return ((int)(unsigned char)(*s1) - (int)(unsigned char)(*s2));
}
