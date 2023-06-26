
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

//print is the copy of enviroment, that was sorted before
//this function only adds declare -x and quotes after first = sign
//and at the end of the value of the env envritoble
//otherwise, everything is printed unchaned
// c is the '=' sign - to save lines of code
//y and x are also sent in to save lines

void	print_quotes(char **print, char c, int y, int x)
{
	int	sign;

	while (print[++y])
	{
		sign = 0;
		x = -1;
		printf("declare -x ");
		while (print[y][++x])
		{
			if (print[y][x] == '"')
				printf("\\");
			if (print[y][x] == '=' && print[y][x + 1] == '\0')
				printf("=%c%c", c, c);
			else if (print[y][x] == '=' && sign == 0)
			{
				sign = 1;
				printf("%c%c", print[y][x], c);
			}
			else if (print[y][x + 1] == '\0')
				printf("%c%c", print[y][x], c);
			else
				printf("%c", print[y][x]);
		}
		printf("\n");
	}
}

//export function with no arguments
int	ft_export_na(char **env, int len)
{
	int		row;
	char	*tmp;
	char	**print;

	print = copy_2d_char_arr(env, len);
	if (print == NULL)
		return (write(2, "Allocation (export_na) problem!\n", 32) && 0);
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
	print_quotes(print, '"', -1, -1);
	free_2d_str_arr(&print);
	return (0);
}

int	ft_append(t_data *data, t_node *node, int y)
{
	int		x;
	char	*result;

	x = 0;
	while (node->cmd[x] != '=')
		x++;
	if (node->cmd[x] == '=')
		x++;
	result = ft_strjoin(data->env_copy[y], &node->cmd[x]);
	if (result == NULL || !result)
		return (0);
	free(data->env_copy[y]);
	data->env_copy[y] = result;
	return (1);
}

//export function when there are arguments
int	ft_export_a(t_data *data, char *var, t_node **node, int len)
{
	int		y;
	char	**new_env;

	y = 0;
	(*node) = (*node)->next;
	if (ft_invalid((*node)->cmd) == 1)
		return (write(2, "not a valid indentifier\n", 24), 0);
	if (ft_replace_existing(data, *node) == 1)
		return (0);
	new_env = copy_2d_char_arr(data->env_copy, len);
	if (new_env == NULL || !new_env)
		return (write(2, "Allocation (export_a) problem\n", 30) && 0);
	while (new_env[y] != NULL)
		y++;
	new_env[y] = malloc(ft_strlen(var) + 1);
	if (new_env[y] == NULL || !new_env[y])
	{
		free_2d_str_arr(&new_env);
		return (write(2, "Allocation (export_a) problem\n", 30) && 0);
	}
	ft_strlcpy(new_env[y], var, ft_strlen(var) + 1);
	new_env[y + 1] = NULL;
	free_2d_str_arr(&data->env_copy);
	data->env_copy = new_env;
	return (0);
}
