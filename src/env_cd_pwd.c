/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cd_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:04:12 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/30 14:12:42 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_home(t_data *data, int i, int found)
{
	char	*home;
	int		x;

	x = -1;
	while (data->env_copy[++x])
	{
		if (ft_strcmp_v2_until("HOME=", data->env_copy[x], '=') == 0)
		{
			found = 1;
			break ;
		}
	}
	if (found == 0)
		return (write(1, "cd: HOME not set\n", 17) && 0);
	while (data->env_copy[x][i] != '=')
		i++;
	home = malloc(ft_strlen(&data->env_copy[x][i + 1]) + 1);
	if (!home || home == NULL)
		return (malloc_error(data), 1);
	ft_strlcpy(home, &data->env_copy[x][i + 1], ft_strlen(&data->env_copy[x][i
			+ 1]) + 1);
	if (chdir(home) != 0)
		perror(NULL);
	free(home);
	return (0);
}

int	ft_cd(t_data *data, char ***args)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	if ((*args)[1] == NULL)
	{
		free_2d_str_arr(args);
		return (cd_home(data, i, found));
	}
	if ((*args)[2] != NULL)
	{
		ft_putstr_fd("too many argumens\n", 2);
		g_ex_status = 1;
		free_2d_str_arr(args);
		return (0);
	}
	if (chdir((*args)[1]) != 0)
	{
		perror(NULL);
		g_ex_status = 1;
	}
	free_2d_str_arr(args);
	return (0);
}

int	ft_pwd(void)
{
	char	dir[500000];

	if (getcwd(dir, sizeof(dir)) == NULL)
	{
		perror(NULL);
		return (1);
	}
	else
		printf("%s\n", dir);
	return (0);
}

int	ft_env(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return (0);
	while (arr[i])
	{
		if (ft_invalid_env(arr[i]) == 2)
			printf("%s\n", arr[i]);
		i++;
	}
	return (0);
}

int	get_arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (-1);
	while (arr[i])
		i++;
	return (i);
}
