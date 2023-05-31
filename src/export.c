
#include "../minishell.h"

char	**copy_2d_char_arr(char **env, int len)
{
	int		y;
	int		z;
	char	**print;

	y = -1;
	z = -1;
	if (!env || !len)
		return (NULL);
	print = malloc((len + 1) * sizeof(char *));
	if (!print)
	{
		perror(NULL);
		return (NULL);
	}
	while (env[++y])
	{
		print[++z] = malloc(ft_strlen(env[y]) + 1);
		if (print[z] == NULL)
			free_2d_str_arr(&print);
		if (print[z] == NULL)
			return (NULL);
		ft_strlcpy(print[z], env[y], ft_strlen(env[y]) + 1);
	}
	print[z + 1] = NULL;
	return (print);
}

void	print_quotes(char **print, char c)
{
	int	y;
	int	x;

	y = -1;
	while (print[++y])
	{
		x = -1;
		write(1, "declare -x ", 11);
		while (print[y][++x])
		{
			if (print[y][x] == '=')
			{
				write(1, &print[y][x], 1);
				write(1, &c, 1);
			}
			else if (print[y][x + 1] == '\0')
			{
				write(1, &print[y][x], 1);
				write(1, &c, 1);
			}
			else
				write(1, &print[y][x], 1);
		}
		write(1, "\n", 1);
	}
}

void	ft_export_na(char **env, t_node **node, int len)
{
	int		row;
	char	*tmp;
	char	**print;

	print = copy_2d_char_arr(env, len);
	if (print == NULL)
		return (perror(NULL));
	while (--len > 0)
	{
		row = -1;
		while (print[++row])
		{
			if (ft_strcmp_v2(print[row], print[row + 1]) > 0
				&& ft_strcmp_v2(print[row], print[row + 1]) != 9999)
			{
				tmp = print[row];
				print[row] = print[row + 1];
				print[row + 1] = tmp;
			}
		}
	}
	row = -1;
	print_quotes(print, '"');
	free_2d_str_arr(&print);
	(*node) = (*node)->next;
}

void	ft_export_a(t_data *data, char *var, t_node **node, int len)
{
	int		y;
	char	**new_env;

	y = 0;
	new_env = copy_2d_char_arr(data->env_copy, len);
	if (new_env == NULL)
		return ;
	while (new_env[y] != NULL)
		y++;
	new_env[y] = malloc(ft_strlen(var) + 1);
	if (new_env[y] == NULL)
	{
		free_2d_str_arr(&new_env);
		return (perror(NULL));
	}
	ft_strlcpy(new_env[y], var, ft_strlen(var) + 1);
	new_env[y + 1] = NULL;
	free_2d_str_arr(&data->env_copy);
	data->env_copy = new_env;
	(*node) = (*node)->next;
	print_quotes(new_env, '"');
}
