
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
			stop = 1;
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
			stop = 1;
		}
		if (str[i + 1] == '\0' && str[i] == '\'')
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	return (0);
}

int	single_quotes_count(char *str)
{
	int	in;
	int	d_qs;

	in = -1;
	d_qs = 0;
	while (str[++in])
	{
		if (str[in] == '\'')
			d_qs++;
	}
	return (d_qs);
}

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

//in case a varable already exist , the function replaces it with the new value
//and return 1 otherwise if the variable is new, return 0 and append it
//to the enviroment
int	ft_replace_existing(t_data *data, t_node *node)
{
	int		y;
	int		match;
	char	*replace;

	y = 0;
	match = -1;
	while (data->env_copy[y])
	{
		if (ft_strcmp_v2_until(data->env_copy[y], node->cmd, '=') == 0)
		{
			match = y;
			break ;
		}
		y++;
	}
	if (match == -1)
		return (0);
	replace = malloc(ft_strlen(node->cmd) + 1);
	if (!replace || replace == NULL)
		return (1);
	ft_strlcpy(replace, node->cmd, ft_strlen(node->cmd) + 1);
	free(data->env_copy[match]);
	data->env_copy[match] = replace;
	return (1);
}
