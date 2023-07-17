/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:38:43 by qtran             #+#    #+#             */
/*   Updated: 2022/10/21 15:52:27 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	di;
	size_t	si;

	di = 0;
	si = 0;
	while (di < size && dst[di])
		di++;
	while (src[si] && (si + di + 1) < size)
	{
		dst[di + si] = src[si];
		si++;
	}
	if (di < size)
		dst[di + si] = '\0';
	return (di + ft_strlen(src));
}
/*
int	main(void)
{
	char	src[];
	char	dst[];

	src[] = "1231";
	dst[] = "Hallo";
	ft_strlcat(dst, src, 7);
	printf("%s\n", dst);
	printf("%zu\n", ft_strlcat(dst, src, 1));
}
 */