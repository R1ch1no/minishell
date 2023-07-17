/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:03:55 by qtran             #+#    #+#             */
/*   Updated: 2022/11/04 18:04:20 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	hexdigits(unsigned long long n)
{
	int	count;

	count = 0;
	while (n >= 16)
	{
		n /= 16;
		count++;
	}
	count++;
	return (count);
}

static char	conv_rem(unsigned long rem, int lower)
{
	if (rem <= 9)
		return (rem + '0');
	else if (rem == 10)
		return ('A' + lower);
	else if (rem == 11)
		return ('B' + lower);
	else if (rem == 12)
		return ('C' + lower);
	else if (rem == 13)
		return ('D' + lower);
	else if (rem == 14)
		return ('E' + lower);
	else if (rem == 15)
		return ('F' + lower);
	return (0);
}

static char	*makehexword(char *word, int count, unsigned long long n, int lower)
{
	unsigned int	rem;

	while (count)
	{
		count--;
		rem = n % 16;
		word[count] = conv_rem(rem, lower);
		n /= 16;
	}
	return (word);
}

int	ft_itohex(unsigned long long n, int lower)
{
	char	*word;
	int		count;
	int		len;

	count = hexdigits(n);
	word = malloc((count + 1) * sizeof(char));
	if (!word)
		return (0);
	word[count] = '\0';
	word = makehexword(word, count, n, lower);
	len = len_putstr(word);
	free(word);
	return (len);
}

/* 
int main ()
{
	char *s = ft_itohex(3423);
	printf("Test: %s", s);
	free(s);
} */