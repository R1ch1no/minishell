/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:17:51 by qtran             #+#    #+#             */
/*   Updated: 2022/10/16 19:10:03 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

/* int main()
{
	char empty1[10] = "ABCD";
	char string1[] = "12";
	//strncpy(empty1, string1, 10);
	//printf("%s\n", empty1);

	ft_strlcpy(empty1, string1, 10);
	printf("%s", empty1);
	printf("\n-------------\n");
} */

/* 	size_t i;
	size_t destsize;

	i = 0;
	destsize = sizeof(dst) / sizeof(char);

	while ((destsize - i * sizeof(char)) && src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	
	return (ft_strlen(src)); */