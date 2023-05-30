
#include "../minishell.h"

void	ft_echo(const char *str, int n)
{
	int	i;

	i = 0;
	if ((!str || str == NULL) && n == 1)
		return ;
	if ((!str || str == NULL) && n == 0)
	{
		write(1, "\n", 1);
		return ;
	}
	while (str[i])
	{
		if (n == 1)
		{
			if (str[i + 1] == '\0' && str[i] == '\n')
				break ;
			else
				write(1, &str[i], 1);
		}
		else
			write(1, &str[i], 1);
		i++;
	}
	if (n == 0)
		write(1, "\n", 1);
}

int	ft_find_match(t_data *data, char *search, int y)
{
	int	x;

	x = 0;
	while (search[x] && data->env_copy[y][x]
		&& search[x] == data->env_copy[y][x])
	{
		if (search[x] == data->env_copy[y][x] && search[x + 1] == '\0')
			return (1);
		x++;
	}
	return (0);
}

void	ft_problem(t_data *data, char **new_env, int z)
{
	free_2d_str_until(new_env, z);
	free_2d_str_arr(&data->env_copy);
	data->env_copy = NULL;
}

int	ft_core(t_data *data, char **new_env, int y, int z)
{
	if (data->env_copy[y])
	{
		new_env[z] = malloc(ft_strlen(data->env_copy[y]) + 1);
		if (!new_env[z])
		{
			ft_problem(data, new_env, z);
			return (1);
		}
		ft_strlcpy(new_env[z], data->env_copy[y], ft_strlen(data->env_copy[y])
			+ 1);
	}
	return (0);
}

void	ft_unset(t_data *data, char *search)
{
	int		y;
	int		z;
	char	**new_env;

	y = 0;
	z = -1;
	while (data->env_copy[y])
		y++;
	new_env = malloc((y + 1) * sizeof(char *));
	if (!new_env)
		return (perror(NULL));
	y = 0;
	while (data->env_copy[y] != NULL)
	{
		++z;
		y += ft_find_match(data, search, y);
		if (ft_core(data, new_env, y, z) == 1)
			return ;
		if (data->env_copy[y] == NULL)
			break ;
		y++;
	}
	free_2d_str_arr(&data->env_copy);
	new_env[z] = NULL;
	data->env_copy = new_env;
}
