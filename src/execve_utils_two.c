/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:04:25 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/29 19:16:07 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	before_start(t_node *node)
{
	DIR	*dir;

	if (ft_strcmp_v2_until(node->cmd, "./", '/') == 0
		|| ft_strcmp_v2_until(node->cmd, "/", '/') == 0)
	{
		dir = opendir(node->cmd);
		if (dir != NULL)
		{
			closedir(dir);
			return (ft_putstr_fd(" Is a directory\n", 2), IS_DIR);
		}
	}
	return (0);
}

void	ft_access_error(t_node *node)
{
	if (ft_strcmp_v2_until(node->cmd, "./", '/') == 0
		|| ft_strcmp_v2_until(node->cmd, "/", '/') == 0)
		ft_putstr_fd(" No such file or directory\n", 2);
	else
	{
		ft_putstr_fd(node->cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		//ft_putstr_fd(": command not found\n", 2);
	}
}
