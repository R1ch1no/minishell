
#include "../minishell.h"

int	closed_with_double(char *str)
{
	int	i;
	int	stop;
	int	count;

	i = 0;
	stop = 0;
	count = 0;
	while (str[i])
	{
		if (i > 0 && stop == 0)
		{
			if (str[i - 1] == '=' && str[i] == '"')
				count++;
		}
		if (str[i + 1] == '\0' && str[i] == '"')
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	return (0);
}

int	closed_with_single(char *str)
{
	int	i;
	int	stop;
	int	count;

	i = 0;
	stop = 0;
	count = 0;
	while (str[i])
	{
		if (i > 0 && stop == 0)
		{
			if (str[i - 1] == '=' && str[i] == '\'')
				count++;
		}
		if (str[i + 1] == '\0' && str[i] == '\'')
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	return (0);
}
