/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:25:48 by qtran             #+#    #+#             */
/*   Updated: 2022/10/21 15:54:23 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 1;
	if (n == 0)
		return (0);
	while (*s1 && *s1 == *s2 && i < n)
	{
		s1++;
		s2++;
		i++;
	}
	return ((int)(unsigned char)(*s1) - (int)(unsigned char)(*s2));
}

/* int	main(void)
{
	char s1[] = "Hallo_1234";
	char s2[] = "Hallox1234a";

	//printf("%d\n", strncmp(s1, s2, 2));
	printf("%d\n", ft_strncmp("t", "", 0));
	//s1 -s2
} */