
#include "../minishell.h"

int	double_quotes_count(char *str)
{
	int	in;
	int	d_qs;

	in = -1;
	d_qs = 0;
	while (str[++in])
	{
		if (str[in] == '"')
			d_qs++;
	}
	return (d_qs);
}

void	ft_adjust_core(char *new, char *str)
{
	int		in;
	int		ind;
	char	c;

	c = '\'';
	in = 0;
	ind = 0;
	while (str[in])
	{
		if (str[in] == c)
			in++;
		if (str[in] == '\0')
			break ;
		new[ind] = str[in];
		ind++;
		in++;
	}
	new[ind] = '\0';
}

int	ft_adjust_single_quotes(char **str)
{
	char	*new;
	char	*temp;

	if (!str)
		return (1);
	temp = (*str);
	new = malloc(ft_strlen(*str) - 2 + double_quotes_count(*str) + 1);
	if (new == NULL || !new)
	{
		perror(NULL);
		return (1);
	}
	ft_adjust_core(new, *str);
	*str = new;
	free(temp);
	return (0);
}
