/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:04:49 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/17 19:35:27 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			else if (print[y][x + 1] == '\0' && sign == 1)
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
		return (ft_putstr_fd("mini_shell : malloc error\n", 2), 1);
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

int	ft_append(t_data *data, char *str, int y, char ***args)
{
	int		x;
	char	*result;

	x = 0;
	while (str[x] != '=')
		x++;
	if (str[x] == '=')
		x++;
	result = ft_strjoin(data->env_copy[y], &str[x]);
	if (result == NULL || !result)
		return (free_2d_str_arr(args), malloc_error(data), 0);
	free(data->env_copy[y]);
	data->env_copy[y] = result;
	return (1);
}

int	export_logic(t_data *data, char ***args, int len, int i)
{
	int		y;
	char	**new_env;

	new_env = copy_2d_char_arr(data->env_copy, len);
	if (new_env == NULL || !new_env)
		return (free_2d_str_arr(args), malloc_error(data), 1);
	y = get_arr_len(new_env);
	new_env[y] = malloc(ft_strlen((*args)[i]) + 1);
	if (new_env[y] == NULL || !new_env[y])
		return (free_2d_str_arr(&new_env), free_2d_str_arr(args),
			malloc_error(data), 1);
	ft_strlcpy(new_env[y], (*args)[i], ft_strlen((*args)[i]) + 1);
	new_env[y + 1] = NULL;
	free_2d_str_arr(&data->env_copy);
	data->env_copy = new_env;
	return (0);
}

//export function when there are arguments
int	ft_export_a(t_data *data, char ***args)
{
	int	i;

	i = 0;
	while ((*args)[++i] != NULL)
	{
		if (ft_invalid((*args)[i]) == 1)
			return (1);
		if (empty_var_exist(data, (*args)[i]) == 1)
			continue ;
		if (ft_replace_existing(data, (*args)[i], args) == 1)
			continue ;
		export_logic(data, args, get_arr_len(data->env_copy) + 1, i);
	}
	return (0);
}
