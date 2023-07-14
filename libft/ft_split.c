/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:20:58 by qtran             #+#    #+#             */
/*   Updated: 2022/12/30 18:46:06 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	howmanysubs(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*(s + i))
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	inotchar(char const *s, char c, int start)
{
	while (*(s + start) && s[start] == c)
	{
		start++;
	}
	return (start);
}

static int	ft_strlentilchar(char const *s, char c, int start)
{
	while (s[start] && s[start] != c)
		start++;
	return (start);
}

static char	**makewords(char **arr, int substrs, char const *s, char c)
{
	int		start;
	int		end;
	int		i;
	int		j;

	i = 0;
	j = -1;
	start = 0;
	end = 0;
	while (i < substrs - 1)
	{
		start = inotchar(s, c, start);
		end = ft_strlentilchar(s, c, start);
		arr[i] = ft_substr(s, start, end - start);
		if (arr[i] == NULL)
		{
			while (++j < i)
				free(arr[j]);
			return (free(arr), NULL);
		}
		start = end;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		substrs;
	char	**arr;

	if (!s)
		return (NULL);
	substrs = howmanysubs(s, c) + 1;
	arr = malloc(sizeof(char *) * substrs);
	if (!arr)
		return (NULL);
	arr = makewords(arr, substrs, s, c);
	return (arr);
}
/* int main ()
{
    char *s = "1234 56";
    char c = ' ';
    char **arr;
    arr = ft_split(s, c);
    printf("%s", arr[0]);
    printf("%s", arr[1]);
    printf("%s", arr[2]);
    //printf("%s", arr[3]);
} */

/*
int	main(void)
{
    char *s = "1-xx-2abc-x-3zzxxxxx4x";
    char **arr;
    int i = 0;
    arr = ft_split(s, 'x');

    while (i <= 4)
    {
        printf("str %d: %s\n", i, arr[i]);
        i++;
    }
    i = 0;

    char *string = "      split   this for   me  !       ";
    arr = ft_split(string, ' ');
    while (i <= 4)
    {
        printf("str %d: '%s'\n", i, arr[i]);
        i++;
    }
    i = 0;
    
    char *s2 = "split  ||this|for|me|||||!|";
    arr = ft_split(s2, '|');
    while (i <= 4)
    {
        printf("str %d: \'%s\'\n", i, arr[i]);
        i++;
    }
    i = 0;
    return (0);
}*/

/*  char *s3 = "aa\0bbb";
    arr = ft_split(s2, 'b');
    while (i <= 4)
    {
        printf("str %d: \'%s\'\n", i, arr[i]);
        i++;
    } 
    return (0);
 */
