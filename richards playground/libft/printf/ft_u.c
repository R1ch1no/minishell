/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:43:34 by qtran             #+#    #+#             */
/*   Updated: 2022/11/04 18:06:12 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	digits(unsigned long int n, int count)
{
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	count++;
	return (count);
}

static char	*makeword(char *word, int count, unsigned long int n)
{
	while (--count >= 0)
	{
		word[count] = n % 10 + '0';
		n /= 10;
	}
	return (word);
}

static char	*ft_itoa_unsigned(unsigned long int n)
{
	char	*word;
	int		count;

	count = 0;
	count = digits(n, count);
	word = malloc((count + 1) * sizeof(char));
	if (!word)
		return (NULL);
	word[count] = '\0';
	return (makeword(word, count, n));
}

int	ft_u(unsigned int n)
{
	char	*str;
	int		len;

	str = ft_itoa_unsigned(n);
	len = len_putstr(str);
	free(str);
	return (len);
}
