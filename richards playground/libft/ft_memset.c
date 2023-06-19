/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:04:56 by qtran             #+#    #+#             */
/*   Updated: 2022/10/08 19:30:21 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
	{
		*p++ = (unsigned char)c;
	}
	return (s);
}

/*int main()
{
    char str[50] = "Aticleworld is a programming Blog.";
	//geht nicht mit pointer weil kein Speicherplatz reserviert wird, angeblich
    printf("\nBefore memset(): %s\n\n", str);
    ft_memset(str + 2, '*', 2);
    printf("After memset(): %s\n\n", str);
    return (0);
}*/