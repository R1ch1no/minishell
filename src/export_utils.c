/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:04:45 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/09 12:43:10 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (NULL);
	while (env[++y])
	{
		print[++z] = malloc(ft_strlen(env[y]) + 1);
		if (print[z] == NULL)
			return (free_2d_str_until(print, z), NULL);
		ft_strlcpy(print[z], env[y], ft_strlen(env[y]) + 1);
	}
	print[z + 1] = NULL;
	return (print);
}

int	ft_invalid(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '=')
	{
		write(2, " not a valid identifier\n", 24);
		g_ex_status = 1;
	}
	if (str[0] <= '9' && str[0] >= '0')
	{
		write(2, " not a valid identifier\n", 24);
		g_ex_status = 1;
	}
	while (str[++i] && str[i] != '=')
	{
		if ((str[i] == '-' && str[i + 1] == '\0') || (str[i] == '-' && str[i
					+ 1] == '='))
		{
			write(2, " not a valid identifier\n", 24);
			g_ex_status = 1;
		}
	}
	if (str[i] == '=' && g_ex_status != 1)
		return (2);
	return (g_ex_status);
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
int	ft_replace_existing(t_data *data, char *str, char ***args)
{
	int		y;
	int		match;
	char	*replace;

	y = -1;
	match = -1;
	while (data->env_copy[++y])
	{
		if (ft_strcmp_export(data->env_copy[y], str, '=') == 0)
		{
			match = y;
			break ;
		}
		if (ft_strcmp_export(data->env_copy[y], str, '=') == -9999)
			return (ft_append(data, str, y, args));
	}
	if (match == -1)
		return (0);
	replace = malloc(ft_strlen(str) + 1);
	if (!replace || replace == NULL)
		return (free_2d_str_arr(args), malloc_error(data), 1);
	ft_strlcpy(replace, str, ft_strlen(str) + 1);
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
