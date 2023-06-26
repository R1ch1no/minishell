
#include "../minishell.h"

int	ft_invalid(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '=')
		ex_status = 1;
	if (str[0] <= '9' && str[0] >= '0')
		ex_status = 1;
	while (str[++i] && str[i] != '=')
	{
		if ((str[i] == '-' && str[i + 1] == '\0') || (str[i] == '-' && str[i
					+ 1] == '='))
					ex_status = 1;
	}
	if (str[i] == '=')
		return (2);
	return (ex_status);
}

int	ft_strcmp_export(char *s1, char *s2, char c)
{
	if (s1 == NULL || s2 == NULL)
		return (9999);
	while (*s1 && *s2 && *s1 == *s2)
	{
		if (*s1 == c && *s2 == c)
			return (0);
		s1++;
		s2++;
	}
	if (*s1 == '=' && *s2 == '+')
		return (-9999);
	return ((int)(unsigned char)(*s1) - (int)(unsigned char)(*s2));
}

//in case a varable already exist , the function replaces it with the new value
//and return 1 otherwise if the variable is new, return 0 and append it
//to the enviroment
int	ft_replace_existing(t_data *data, t_node *node)
{
	int		y;
	int		match;
	char	*replace;

	y = -1;
	match = -1;
	while (data->env_copy[++y])
	{
		if (ft_strcmp_export(data->env_copy[y], node->cmd, '=') == 0)
		{
			match = y;
			break ;
		}
		if (ft_strcmp_export(data->env_copy[y], node->cmd, '=') == -9999)
			return (ft_append(data, node, y));
	}
	if (match == -1)
		return (0);
	replace = malloc(ft_strlen(node->cmd) + 1);
	if (!replace || replace == NULL)
		return (write(2, "Allocation (export_a) error !\n", 30) && 1);
	ft_strlcpy(replace, node->cmd, ft_strlen(node->cmd) + 1);
	free(data->env_copy[match]);
	data->env_copy[match] = replace;
	return (1);
}

int	ft_invalid_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (2);
	return (0);
}
