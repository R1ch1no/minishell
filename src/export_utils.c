
#include "../minishell.h"

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

void	ft_adjust_core(char *new, char *str)
{
	int		sign;
	int		in;
	int		ind;
	char	c;

	c = '\'';
	in = 0;
	ind = 0;
	sign = 0;
	while (str[in])
	{
		if ((str[in] == c || str[in] == '"') && str[in - 1] == '=' && sign == 0)
		{
			sign = 1;
			in++;
		}
		if ((str[in] == c || str[in] == '"') && str[in + 1] == '\0')
			in++;
		if (str[in] == '\0')
			break ;
		new[ind] = str[in];
		ind++;
		in++;
	}
	new[ind] = '\0';
}

int	ft_adjust_single_quotes(char **str, t_node *node)
{
	char	*new;
	char	*tmp;

	if (!str)
		return (1);
	tmp = node->cmd;
	new = malloc(ft_strlen(*str) - 2 + double_quotes_count(*str) + 1);
	if (new == NULL || !new)
	{
		perror(NULL);
		return (1);
	}
	ft_adjust_core(new, *str);
	node->cmd = new;
	free(tmp);
	return (0);
}

int	ft_replace_existing(t_data *data, t_node *node)
{
	int		y;
	int		match;
	char	*replace;
	char	*tmp;

	y = -1;
	match = 0;
	while (data->env_copy[++y])
		if (ft_strcmp_v2(data->env_copy[y], node->cmd) == 0)
			match = y;
	if (match == 0)
		return (0);
	tmp = data->env_copy[match];
	replace = malloc(ft_strlen(node->cmd) + 1);
	if (!replace || replace == NULL)
		return (1);
	ft_strlcpy(replace, node->cmd, ft_strlen(node->cmd) + 1);
	data->env_copy[match] = replace;
	free(tmp);
	return (1);
}
