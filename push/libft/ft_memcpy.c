/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:05:05 by qtran             #+#    #+#             */
/*   Updated: 2022/10/25 18:34:42 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*srcptr;
	unsigned char		*destptr;
	unsigned int		i;

	srcptr = src;
	destptr = dest;
	i = 0;
	if (!dest && !src)
		return (dest);
	while (i < n)
	{
		*(destptr + i) = *(srcptr + i);
		i++;
	}
	return (dest);
}

/* int main()
{
    char src[] = "12345";
    char dest[] = "abcde";
    ft_memmove(dest, src, 5)
    printf("Test: %s", (char *)ft_memmove(dest, src, 5));
} */
