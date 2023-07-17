/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:26:25 by qtran             #+#    #+#             */
/*   Updated: 2022/10/16 19:13:09 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ss1;
	const unsigned char	*ss2;
	size_t				i;

	i = 0;
	ss1 = (const unsigned char *)s1;
	ss2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}

/* int	main(void)
{
	char s1[] = "\xff\xaa\xde\x12";
	printf("%s\n", s1);
	char s2[] = "\xff\xaa\xde\x12MACOSAAAAA";
	printf("%s\n", s2);

	printf("%d\n", ft_memcmp(s1, s2, 4));
	//printf("%d\n", memcmp(s1, s2, 5));
	//s1 -s2
} */