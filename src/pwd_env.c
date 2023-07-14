/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:11:56 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/14 12:11:58 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*mine_strjoin(char *str1, char *str2, int no)
{
	char	*jstr;
	int		i;
	int		j;

	if (!str1 || str1 == NULL || !str2 || str2 == NULL)
		return (NULL);
	jstr = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2)) 
			+ 1);
	if (!jstr || jstr == NULL)
		return (NULL);
	j = 0;
	i = -1;
	while (str1[++i])
		jstr[i] = str1[i];
	while (str2[j])
		jstr[i++] = str2[j++];
	jstr[i] = '\0';
	if (no == 1)
		free(str1);
	return (jstr);
}

int	find_index(t_data *data, char *str)
{
	int	x;
	int	match;

	x = -1;
	match = -1;
	while (data->env_copy[++x])
	{
		if (ft_strcmp_v2_until(str, data->env_copy[x], '=') == 0)
		{
			match = x;
			return (match);
		}
	}
	return (match);
}

int	pwd_change(t_data *data, int from, int to, char *variable)
{
	char	*path;
	char	*pwdd;
	int		i;

	i = 0;
	if (from == -1 || to == -1)
		return (0);
	while (data->env_copy[from][i] != '=')
		i++;
	path = malloc(ft_strlen(&data->env_copy[from][i + 1]) + 1);
	if (!path || path == NULL)
		return (1);
	ft_strlcpy(path, &data->env_copy[from][i + 1],
		ft_strlen(&data->env_copy[from][i + 1]) + 1);
	pwdd = ft_strjoin(variable, path);
	if (!pwdd)
		return (free(path), 1);
	free(data->env_copy[to]);
	data->env_copy[to] = pwdd;
	free(path);
	return (0);
}

int	pwd_change_two(t_data *data, char *cwd, int to, char *variable)
{
	char	*path;
	int		i;

	i = 0;
	if (!cwd || to == -1)
		return (0);
	while (cwd[i])
		i++;
	path = mine_strjoin(variable, cwd, 0);
	if (!path || path == NULL)
		return (1);
	free(data->env_copy[to]);
	data->env_copy[to] = path;
	return (0);
}

void	ft_pwd_env(t_data *data, char ***args)
{
	char	dir[500000];
	char	**arr;

	if (getcwd(dir, sizeof(dir)) == NULL)
		return ;
	data->pwd = find_index(data, "PWD=");
	data->old_pwd = find_index(data, "OLDPWD=");
	if (data->old_pwd == -1 && data->pwd != -1)
	{
		arr = malloc(2 * sizeof(char *));
		if (!arr)
			return (free_2d_str_arr(args), malloc_error(data));
		arr[0] = (char *)malloc(ft_strlen("OLDPWD=") + 1);
		if(!arr[0])
			return (free(arr), free_2d_str_arr(args), malloc_error(data));
		arr[1] = NULL;
		ft_strlcpy(arr[0], "OLDPWD=", ft_strlen("OLDPWD=") + 1);
		export_logic(data, &arr, get_arr_len(data->env_copy) + 1, 0);
		data->old_pwd = find_index(data, "OLDPWD=");
		free_2d_str_arr(&arr);
	}
	if (pwd_change(data, data->pwd, data->old_pwd, "OLDPWD=") == 1)
		return (free_2d_str_arr(args), malloc_error(data));
	if (pwd_change_two(data, dir, data->pwd, "PWD=") == 1)
		return (free_2d_str_arr(args), malloc_error(data));
}
