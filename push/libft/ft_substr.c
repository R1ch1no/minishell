/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:23:22 by qtran             #+#    #+#             */
/*   Updated: 2023/05/22 17:40:40 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;
	unsigned int	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	i = 0;
	if (slen <= start)
		len = 0;
	else if (slen > start && slen - start < len)
		len = slen - start;
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* int main()
{
    char const *str = "1234";
    printf("Substr: %s ", ft_substr(str, 5, 4));
} */