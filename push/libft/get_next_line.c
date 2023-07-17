/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:24:43 by qtran             #+#    #+#             */
/*   Updated: 2023/01/25 20:18:22 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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
	while (ft_strchr(str, '\n') == NULL && check != 0)
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check == -1)
		{
			free(buf);
			free(str);
			return (NULL);
		}
		buf[check] = '\0';
		str = ft_strjoin(str, buf);
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
	temp = (char *)malloc(ft_strlen(str) - i + 1);
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
	static char	*str;
	size_t		i;
	char		*oneline;

	if (BUFFER_SIZE == 0 || fd < 0)
		return (NULL);
	str = read_file(fd, str);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	oneline = ft_substr(str, 0, i + 1);
	str = new_str(str, i + 1);
	return (oneline);
}

/* int	main(int ac, char **av)
{
	int		fd;
	int		i;
	int		lines;
	char	*gnl;

	fd = open("Text.txt", O_RDONLY);
	printf("fd=%d", fd);
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
}*/

/* 
int	main(void)
{
	int fd;
	int fd2;
	//int stdin;

	fd = open("Numbers.txt", O_RDONLY);
	fd2 = open("Text.txt", O_RDONLY);
	//stdin = 0;

	int i = 1;
	int lines = 15;
	char *gnl;

	while (lines != 0)
	{
		//PRINTF ERSETZEN
		gnl = get_next_line(fd);
		printf("line %d:%s", i, gnl);
		i++;
		lines--;
		free(gnl);
	}
	lines = 15;
	i = 1;
	printf("********New File*******\n");
	while (lines != 0)
	{
		//PRINTF ERSETZEN
		gnl = get_next_line(fd2);
		printf("line %d:%s", i, gnl);
		i++;
		lines--;
		free(gnl);
	}
	lines = 15;
	i = 1;
	printf("********New File*******\n");
	while (lines != 0)
	{
		//PRINTF ERSETZEN
		gnl = get_next_line(fd2);
		printf("line %d:%s", i, gnl);
		i++;
		lines--;
		free(gnl);
	}
	close(fd);
	close(fd2);
	//close(stdin);
	lines = 15;
	i = 1;
	printf("********Stdin*******\n");
	while (lines != 0)
	{
		//PRINTF ERSETZEN
		gnl = get_next_line(fd2);
		printf("line %d:%s", i, gnl);
		i++;
		lines--;
		free(gnl);
	}
	printf("Main says: THE END");
	return (0);
} */
