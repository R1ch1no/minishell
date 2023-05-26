/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:56:43 by rkurnava          #+#    #+#             */
/*   Updated: 2023/05/26 14:48:32 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(const char *path)
{
	if (!path)
		return (1);
	if (path[0] == '\0')
		return (1);
	if (access(path, R_OK) == 0)
	{
		if (chdir(path) != 0)
			return (1);
		return (0);
	}
	return (1);
}

void	ft_pwd(void)
{
	char	dir[500000];

	if (getcwd(dir, sizeof(dir)) != NULL)
		printf("%s\n", dir);
}

void	ft_echo(const char *str, int n)
{
	int	i;

	i = 0;
	if (!str && n == 0)
	{
		write(1, "\n", 1);
		return ;
	}
	while (str[i])
	{
		if (n == 1)
		{
			if (str[i + 1] == '\0' && str[i] == '\n')
				break ;
			else
				write(1, &str[i], 1);
		}
		else
			write(1, &str[i], 1);
		i++;
	}
	if (n == 0)
		write(1, "\n", 1);
}
