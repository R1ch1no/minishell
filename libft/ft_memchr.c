/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:31:03 by qtran             #+#    #+#             */
/*   Updated: 2022/10/25 18:40:51 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	*ft_memchr(const void *s, int x, size_t n)
{
	unsigned char		c;
	const unsigned char	*temp;
	size_t				i;

	c = x;
	temp = s;
	i = 0;
	if (n == 0)
		return (0);
	while (*(temp + i) != c && i < n - 1)
		i++;
	if (*(temp + i) == c)
		return ((void *)(s + i));
	else
		return (0);
}

/* int main()
{
    const char *s = "abcdefuckyou";
    //printf("Return: %s", (char *)ft_memchr(s, 'f', 3));
    printf("Return: %p", memchr(s, 'f', 7));

	//NULL-bytes sollen auch verglichen werden da sie memory sind
    return (0);
} */