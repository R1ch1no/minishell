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

void	check_for_dollar(char **line, t_data *data)
{
	int		i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
			i += subout_dollar(line, i, FALSE, data);
		else
			i++;
	}
}
