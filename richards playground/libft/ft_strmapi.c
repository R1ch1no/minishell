/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:40:56 by qtran             #+#    #+#             */
/*   Updated: 2022/10/30 15:43:02 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

/* char f(unsigned int ix, char c )
{
	int		i;
	char	*nstr;

    if (ix)
        c = c + 1;
    return (c);
} */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*nstr;

	i = 0;
	if (!s)
		return (NULL);
	nstr = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!nstr)
		return (NULL);
	while (s[i])
	{
		nstr[i] = f(i, s[i]);
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}

/* int main()
{
    char *s = "abcxyz135";
    char *new = ft_strmapi(s, f);
    printf("new: %s", new);

    return (0);
} */
