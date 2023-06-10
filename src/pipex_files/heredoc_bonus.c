/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:20:31 by qtran             #+#    #+#             */
/*   Updated: 2023/06/10 13:19:14 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//solls auch mit 1 cmd funcktionieren?
int	check_if_here_doc(int ac, char **av)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac == 6)
			return (1);
		else
			exit(0);
	}
	return (0);
}

int	here_doc(t_data *data)
{
	char	*line;

	data->fd_heredoc = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (data->here_doc == -1)
		cleanup(data);
	while (1)
	{
		line = readline("💩");
		if (ft_strcmp(line, data->limiter) == 0)
		{
			free(line);
			break ;
		}
		write(data->fd_heredoc, line, ft_strlen(line));
		free(line);
	}
	close(data->fd_heredoc);
	data->here_doc = open(HERE_DOC, O_RDONLY);
	if (data->here_doc < 0)
		unlink(".heredoc_tmp");
	return (0);
}
