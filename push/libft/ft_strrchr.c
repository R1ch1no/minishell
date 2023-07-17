/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:04:28 by qtran             #+#    #+#             */
/*   Updated: 2022/10/28 17:20:20 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (s[i] != (char)c && i > 0)
		i--;
	if (s[i] == (char)(c))
		return ((char *)(&s[i]));
	else
		return (NULL);
}

/* int main()
{
    const char *s = "abcdeck";
    printf("Return: %s", ft_strrchr(s, 'c'));
    return (0);
    // return(s + i) geht auch
} */