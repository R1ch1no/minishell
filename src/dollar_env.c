/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:01:29 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/29 18:01:31 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_of_env_val(char *str)
{
	int		i;

	i = 0;
	while (str && str[i] != '=')
	{
		i++;
	}
	return (i);
}

char	*get_env_value(char *look_for, char **env)
{
	char		*env_value;
	char		*start;
	size_t		len;
	int			i;

	i = -1;
	while (env[++i])
	{
		len = len_of_env_val(env[i]);
		if (ft_strncmp(look_for, env[i], len) == 0
			&& ft_strlen(look_for) == len)
		{
			start = ft_strchr(env[i], '=');
			env_value = ft_strdup(++start);
			break ;
		}
	}
	if (env[i] == NULL)
		env_value = ft_strdup("");
	if (!env_value)
		return (NULL);
	return (env_value);
}

char	*get_last_exit_status(char **end_of_d, int ret_value)
{
	char	*status;

	if (!end_of_d)
		return (NULL);
	status = ft_itoa(ret_value);
	(*end_of_d)++;
	return (status);
}
