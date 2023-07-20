/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:04:56 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/29 18:04:57 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_heredoc_child(t_data *data)
{
	close_prev_fd(&data->fd_heredoc);
	ft_clean_cmd(data);
	free_2d_str_arr(&data->env_copy);
	free(data);
}

int	hd_subout_dollar(char **str, int i, t_data *data)
{
	char	*before_d;
	char	*d_name;
	char	*env_value;
	char	*end_of_d;

	i++;
	if (check_if_quote_and_closed((*str), i) == TRUE)
		return (strcpy_wout_ind(str, i - 1), 0);
	before_d = get_str_before_dollar(*str, i);
	end_of_d = get_end_of_dollar(*str, i);
	d_name = ft_substr(*str, i, end_of_d - &(*str)[i]);
	if ((*str)[i] == '?')
		env_value = get_last_exit_status(&end_of_d, g_ex_status);
	else
		env_value = get_env_value(d_name, TRUE, NULL, data);
	if ((!before_d) || (!end_of_d) || (!d_name) || (!env_value))
		cleanse(data);
	if (subbing_cmd_str(str, before_d, env_value, end_of_d) == 1)
		cleanse(data);
	i = ft_strlen(env_value);
	return (four_free(d_name, before_d, env_value, NULL), i);
}

void	check_for_dollar(char **line, t_data *data)
{
	int		i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
			i += hd_subout_dollar(line, i, data);
		else
			i++;
	}
}
