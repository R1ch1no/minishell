
#include "../minishell.h"

int	count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	cut_out_all(char *str, char c, char *cutted)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			cutted[j] = str[i];
			j++;
		}
		i++;
	}
	cutted[j] = '\0';
}

void	cut_out_all_but_last(char *str, char c, char *cutted)
{
	int		i;
	int		j;
	char	*last_char;

	i = ft_strlen(str);
	while (str[i] != c)
		i--;
	last_char = &str[i];
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c || &str[i] == last_char)
		{
			cutted[j] = str[i];
			j++;
		}
		i++;
	}
	cutted[j] = '\0';
}

void	cut_out_quotes(char **str, char c)
{
	int		count;
	char	*cutted;

	if (!str)
		return ;
	count = count_char((*str), c);
	if (count < 2)
		return ;
	if (count % 2 == 0)
	{
		cutted = malloc(sizeof(char) * (ft_strlen((*str)) - count + 1));
		cut_out_all(*str, c, cutted);
	}
	else
	{
		cutted = malloc(sizeof(char) * (ft_strlen(*str) - (count - 1) + 1));
		cut_out_all_but_last(*str, c, cutted);
	}
	free(*str);
	*str = cutted;
}
