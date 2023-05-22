/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:25:48 by qtran             #+#    #+#             */
/*   Updated: 2023/05/22 16:39:01 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (9999);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((int)(unsigned char)(*s1) - (int)(unsigned char)(*s2));
}

char	*my_strcmp(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (NULL);
		s1++;
		s2++;
	}
	return (s1);
}
/*
int	main(void)
{
	char *s1 = malloc(sizeof(char) * 5);
	s1[0] = '1';
	s1[1] = '2';
	s1[2] = '\0';

	char *s2 = "12";
	//char s1[] = "Halloa";
	//char s2[] = "Halloa";
	

	char *s3 = NULL;
	char *s4 = NULL;
	printf("%d\n", ft_strcmp(s1, s2));
	printf("%d\n", ft_strcmp(s3, s4));


	printf("-------------------------\nTESTING my_strcmp():\n");
	if (my_strcmp(s1, s2) == NULL)
		printf("Not equal\n");
	else
		printf("equal, here is the string. %s\n", s1);

	if (my_strcmp(s3, s4) == NULL)
		printf("Not equal\n");
	else
		printf("equal\n");
	free(s1);
}*/
