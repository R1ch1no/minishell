
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

void	ft_adjust_core(char *new, char *str, char rem)
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
		if ((str[in] == c || str[in] == rem) && str[in - 1] == '=' && sign == 0)
		{
			sign = 1;
			in++;
		}
		if ((str[in] == c || str[in] == rem) && str[in + 1] == '\0')
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
	int		rem;
	char	*new;
	char	*tmp;

	if (!str)
		return (1);
	rem = -2;
	tmp = node->cmd;
	if (single_quotes_count(*str) == 0 || double_quotes_count(*str) == 0)
		rem = 0;
	new = malloc(ft_strlen(*str) + rem + double_quotes_count(*str) + 1);
	if (new == NULL || !new)
		return (write(2, "Allocation failed!\n", 19) && 1);
	if (closed_with_double(*str))
		ft_adjust_core(new, *str, '"');
	if (closed_with_single(*str))
		ft_adjust_core(new, *str, '\'');
	node->cmd = new;
	free(tmp);
	return (0);
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
