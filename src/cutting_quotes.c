
#include "minishell.h"

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
		//if (!cuted)
		//cleanse(data)
		cut_out_all(*str, c, cutted);
	}
	else
	{
		cutted = malloc(sizeof(char) * (ft_strlen(*str) - (count - 1) + 1));
		//if (!cuted)
		//cleanse(data)
		cut_out_all_but_last(*str, c, cutted);
	}
	free(*str);
	*str = cutted;
}

/*
int	main(void)
{
    char *none = ft_strdup("Test");
    char *one = ft_strdup("Test\"");
    char *three = ft_strdup("T \"e \"st\"");
    char *four = ft_strdup("T \"e \"s \"t\"");

    printf("%s\n", none);
    cut_out_quotes(&none, '"');
    printf("%s\n", none);
    free(none);

    printf("%s\n", one);
    cut_out_quotes(&one, '"');
    printf("%s\n", one);
    free(one);

    printf("%s\n", three);
    cut_out_quotes(&three, '"');
    printf("%s\n", three);
    free(three);
    
    printf("%s\n", four);
    cut_out_quotes(&four, '"');
    printf("%s\n", four);
    free(four);
}*/