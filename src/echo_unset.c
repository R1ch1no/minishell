/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:04:08 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/20 16:04:57 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//echo receives node that comes after the node containing cmd "echo"
int	ft_echo(t_node **node)
{
	int	n;

	n = 0;
	if ((*node) == NULL)
		return (write(1, "\n", 1) && 0);
	while (echo_flag((*node)->cmd) == 1)
	{
		n = 1;
		(*node) = (*node)->next;
		continue ;
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

int	unset(t_data *data, char *search, char ***args)
{
	int		y;
	int		z;
	char	**new_env;

	z = -1;
	y = len_2d_str_arr(data->env_copy);
	if ((*args)[1] == NULL || search == NULL || ft_find(data, search) == 0)
		return (free_2d_str_arr(args), 0);
	new_env = malloc((y) * sizeof(char *));
	if (!new_env || new_env == NULL)
		return (free_2d_str_arr(args), malloc_error(data), 1);
	y = -1;
	while (data->env_copy[++y] != NULL)
	{
		if (ft_find_match(data, search, y) == 0)
			if (ft_core(data, new_env, y, ++z) == 1)
				return (free_2d_str_arr(args), exit(1), 1);
		if (data->env_copy[y] == NULL)
			break ;
	}
	free_2d_str_arr(&data->env_copy);
	new_env[z + 1] = NULL;
	data->env_copy = new_env;
	return (2);
}

int	ft_unset(t_data *data, char ***args)
{
	int	i;
	int	ret;

	i = 0;
	ret = -1;
	while ((*args)[++i])
	{
		ret = unset(data, (*args)[i], args);
		if (ret == 0 || ret == 1)
			break ;
	}
	if (ret == 0 || ret == 1)
		return (free_2d_str_arr(args), ret);
	else
		return (free_2d_str_arr(args), 0);
}
