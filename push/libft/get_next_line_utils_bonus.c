/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:25:03 by qtran             #+#    #+#             */
/*   Updated: 2022/11/18 19:17:11 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

char	*gnl_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != (char)c && s[i])
		i++;
	if (s[i] == (char)c)
		return ((char *)(&s[i]));
	else
		return (NULL);
}

size_t	gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*gnl_strjoin_extension(char *s1)
{
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
		return (s1);
	}
	return (s1);
}

char	*gnl_strjoin(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	s1 = gnl_strjoin_extension(s1);
	if (!s1 || !s2)
		return (NULL);
	temp = (char *)malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!temp)
		return (NULL);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[j])
		temp[i++] = s2[j++];
	temp[i] = '\0';
	free(s1);
	return (temp);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;
	unsigned int	slen;

	if (!*s)
		return (NULL);
	slen = gnl_strlen(s);
	i = 0;
	if (slen <= start)
		len = 0;
	else if (slen > start && slen - start < len)
		len = slen - start;
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
