
#include "../minishell.h"

//echo receives node that comes after the node containing cmd "echo"
int	ft_echo(t_node **node)
{
	int	n;

	signal(SIGPIPE, SIG_IGN);
	n = 0;
	if ((*node) == NULL)
		return (write(1, "\n", 1) && 0);
	if (ft_strcmp_v2((*node)->cmd, "-n") == 0)
	{
		n = 1;
		(*node) = (*node)->next;
	}
	if ((*node) == NULL && n == 1)
		return (0);
	echo_print(node, n);
	if (n == 1)
		return (0);
	return (write(1, "\n", 1) && 0);
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
			new_env[z] = NULL;
			ft_problem(data, new_env, z);
			return (1);
		}
		ft_strlcpy(new_env[z], data->env_copy[y], ft_strlen(data->env_copy[y])
			+ 1);
	}
	return (0);
}

int	ft_unset(t_data *data, char *search, char ***args)
{
	int		y;
	int		z;
	char	**new_env;

	z = -1;
	y = len_2d_str_arr(data->env_copy);
	if ((*args)[1] == NULL || search == NULL || ft_find(data, search) == 0)
		return (free_2d_str_arr(args), 0);
	new_env = malloc((y) * sizeof(char *));
	if (!new_env)
		return (write(2, "Allocation error (unset) !\n", 27),
			free_2d_str_arr(args), 0);
	y = -1;
	while (data->env_copy[++y] != NULL)
	{
		if (ft_find_match(data, search, y) == 0)
			if (ft_core(data, new_env, y, ++z) == 1)
				return (free_2d_str_arr(args), 0);
		if (data->env_copy[y] == NULL)
			break ;
	}
	free_2d_str_arr(&data->env_copy);
	new_env[z + 1] = NULL;
	data->env_copy = new_env;
	return (free_2d_str_arr(args), 0);
}
