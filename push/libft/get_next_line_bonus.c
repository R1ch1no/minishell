/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:24:43 by qtran             #+#    #+#             */
/*   Updated: 2022/11/18 19:18:08 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char	*read_file(int fd, char *str)
{
	char	*buf;
	int		check;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	check = 1;
	while (gnl_strchr(str, '\n') == NULL && check != 0)
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check == -1)
		{
			free(buf);
			free(str);
			return (NULL);
		}
		buf[check] = '\0';
		str = gnl_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*new_str(char *str, int i)
{
	char	*temp;
	int		n;

	if (!str[i - 1])
	{
		free(str);
		return (NULL);
	}
	temp = (char *)malloc(gnl_strlen(str) - i + 1);
	if (!temp)
		return (NULL);
	n = 0;
	while (str[i])
	{
		temp[n] = str[i];
		i++;
		n++;
	}
	temp[n] = '\0';
	free(str);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	size_t		i;
	char		*oneline;

	if (BUFFER_SIZE == 0 || fd < 0)
		return (NULL);
	str[fd] = read_file(fd, str[fd]);
	if (str[fd] == NULL)
		return (NULL);
	i = 0;
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
		i++;
	oneline = gnl_substr(str[fd], 0, i + 1);
	str[fd] = new_str(str[fd], i + 1);
	return (oneline);
}

/* 
int	main(int ac, char **av)
{
	int		fd;
	int		i;
	int		lines;
	char	*gnl;
	int		fd_numb;
	int		fd_text;

	fd = open("Text.txt", O_RDONLY);
	i = 1;
	lines = atoi(av[1]);
	if (ac == 2)
	{
		while (lines != 0)
		{
			gnl = get_next_line(fd);
			printf("line %d:%s", i, gnl);
			i++;
			lines--;
			free(gnl);
		}
		close(fd);
		printf("Main says: THE END");
		return (0);
	}
	else
	{
		close(fd);
		printf("Main says: THE END");
		return (0);
	}
} */
/* 
void	bonus_test(int fd, int lines);
int	main(void)
{
	//int stdin;
	fd_numb = open("Numbers.txt", O_RDONLY);
	fd_text = open("Text.txt", O_RDONLY);
	//stdin = 0;
	printf("********Numbers*******\n");
	printf("readfile");
	printf("********Numbers*******\n");
	printf("readfile");
	
	bonus_test(fd_numb, 3);
	printf("********Text*******\n");
	bonus_test(fd_text, 4);
	printf("********Numbers 2*******\n");
	bonus_test(fd_numb, 2);
	printf("********Text 2*******\n");
	bonus_test(fd_text, 2);
	close(fd_numb);
	close(fd_text);
	//close(stdin);
	printf("********Stdin*******\n");
	while (lines != 0)
	{
		gnl = get_next_line(stdin);
		printf("line %d:%s", i, gnl);
		i++;
		lines--;
		free(gnl);
	}
	printf("Main says: THE END");
	return (0);
}

void	bonus_test(int fd, int lines)
{
	int i = 1;
	char *gnl;
	printf("readfile");
	while (lines != 0)
	{
		gnl = get_next_line(fd);
		printf("line %d:%s", i, gnl);
		i++;
		lines--;
		free(gnl);
	}
} */
