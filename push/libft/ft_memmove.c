/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:05:01 by qtran             #+#    #+#             */
/*   Updated: 2022/10/25 18:33:48 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	if (!dest && !src)
	{
		return (0);
	}
	s = (char *)src;
	d = (char *)dest;
	i = 0;
	if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

/* int main()
{
    char src[] = "123abc";
    char dest[] = "";

    //printf("Test: %s", (char *)ft_memmove(&src[2], src, 3));
    printf("Test: %s\n", (char *)ft_memmove(dest, &src[3], 1));
} */
