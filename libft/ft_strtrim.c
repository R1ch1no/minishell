/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:00:17 by qtran             #+#    #+#             */
/*   Updated: 2023/05/22 18:04:02 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*cpy;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	cpy = ft_substr((char *)s1, 0, i + 1);
	return (cpy);
}

/* int main()
{
    char const *s1 = "";
    char const *set = "b";
    char *x = ft_strtrim(s1, set);
    printf("Trimed: %s", x);
} */