/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:10:37 by qtran             #+#    #+#             */
/*   Updated: 2023/06/06 15:04:38 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	digits(int n, int count)
{
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	count++;
	return (count);
}

char	*makeword(char *word, int count, int sign, int n)
{
	while (--count >= sign)
	{
		word[count] = n % 10 + '0';
		n /= 10;
	}
	if (sign == 2)
		word[1] = '2';
	if (sign >= 1)
		word[0] = '-';
	return (word);
}

char	*ft_itoa(int n)
{
	char	*word;
	int		count;
	int		sign;

	count = 0;
	sign = 0;
	if (n == -2147483648)
	{
		n = 147483648;
		count += 2;
		sign = 2;
	}
	else if (n < 0)
	{
		sign = 1;
		n = -n;
		count++;
	}
	count = digits(n, count);
	word = malloc((count + 1) * sizeof(char));
	if (!word)
		return (NULL);
	word[count] = '\0';
	return (makeword(word, count, sign, n));
}

/* int main ()
{
    printf("word:%s", ft_itoa(-3323));
    return (0);
    //-2147483647-1
}
 */