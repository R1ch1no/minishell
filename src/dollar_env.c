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
void expand_spaces(char *env_value, t_node *node)
{
	char **arr;

	arr = ft_split(env_value, ' ');
	if (!arr)
		return ;
	(void)node;
	
}

char	*get_env_value(char *look_for, t_data *d) //, int lfc)
{
	char		*env_value;
	char		*start;
	size_t		len;
	int			i;

	i = -1;
	while (d->env_copy[++i])
	{
		len = len_of_env_val(d->env_copy[i]);
		if (ft_strncmp(look_for, d->env_copy[i], len) == 0
			&& ft_strlen(look_for) == len)
		{
			start = ft_strchr(d->env_copy[i], '=');
			env_value = ft_strdup(++start);
			break ;
		}
	}
	if (d->env_copy[i] == NULL)
		env_value = ft_strdup("");
	if (!env_value)
		return (NULL);
	//if (ft_strchr(env_value, ' ') != NULL && lfc == FALSE)
	//	expand_spaces(env_value, NULL);
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
