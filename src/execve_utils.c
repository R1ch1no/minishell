/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:04:31 by rkurnava          #+#    #+#             */
/*   Updated: 2023/07/13 18:16:51 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_access(char **tmp, t_node *node, int *m_error)
{
	char	*path;
	int		i;
	int		cmdlen;
	int		tlen;

	i = -1;
	cmdlen = ft_strlen(node->cmd);
	while (tmp[++i])
	{
		tlen = ft_strlen(tmp[i]);
		path = malloc(tlen + 1 + cmdlen + 1);
		if (path == NULL || !path)
			return (*m_error = 1, NULL);
		ft_strlcpy(path, tmp[i], tlen + 1);
		ft_strlcpy(&path[tlen], "/", 2);
		ft_strlcpy(&path[tlen + 1], node->cmd, tlen + 1 + cmdlen);
		if (access(path, X_OK | F_OK) == 0)
			return (path);
		free(path);
	}
	ft_access_error(node);
	path = NULL;
	return (path);
}

char	*ft_exec_access(char *env, t_node *node, int *m_error)
{
	char	**tmp;
	char	*path;
	int		i;

	i = 0;
	while (env[i] != '=' && env[i])
		i++;
	if (env[i] == '=')
		i++;
	if (env[i] == '\0')
		return (NULL);
	tmp = ft_split(&env[i], ':');
	if (tmp == NULL)
	{
		*m_error = 1;
		return (NULL);
	}
	path = check_access(tmp, node, m_error);
	free_2d_str_arr(&tmp);
	return (path);
}

char	*search_path(char **env, t_node *node, int *m_error)
{
	int	y;
	int	x;
	int	found;

	y = -1;
	x = 0;
	found = 0;
	while (env[++y])
	{
		if (ft_strcmp_v2_until(env[y], "PATH=", '=') == 0)
		{
			found = y;
			break ;
		}
	}
	while (found != 0 && env[found][x] != '=' && env[found][x])
		x++;
	if (env[found][x] == '=')
		x++;
	if (found == 0 || env[found][x] == '\0')
		return (ft_putstr_fd(node->cmd, 2),
			ft_putstr_fd(": No such file or directory\n", 2), NULL);
	return (ft_exec_access(env[y], node, m_error));
}

//runs an executable from the current folder with ./
int	ft_exec_here(char **path, t_node *node, char ***args)
{
	int	code;

	code = 0;
	*path = malloc(ft_strlen(node->cmd) + 1);
	if (!path || path == NULL)
		return (1);
	ft_strlcpy(*path, node->cmd, ft_strlen(node->cmd) + 1);
	*args = malloc((arg_num(node) + 1) * sizeof(char *));
	if (!args || args == NULL)
	{
		free(*path);
		return (1);
	}
	*args[0] = NULL;
	if (access(*path, F_OK) != 0)
		code = CMD_N_F;
	else if (access(*path, X_OK) != 0)
		code = NO_RIGHTS;
	if (code != 0)
	{
		perror(NULL);
		free(*path);
		free(*args);
	}
	return (code);
}

int	ft_exec_path(char **env, char **path, t_node *node, char ***args)
{
	int	m_error;

	m_error = 0;
	*args = malloc((arg_num(node) + 1) * sizeof(char *));
	if (!args || args == NULL)
		return (1);
	*args[0] = NULL;
	if (access(node->cmd, F_OK) == 0 && node->cmd[0] == '/')
	{
		*path = ft_strdup(node->cmd);
		if (path == NULL)
			return (free_2d_str_arr(args), 1);
	}
	else
		*path = search_path(env, node, &m_error);
	if (*path == NULL && m_error == 0)
		return (free_2d_str_arr(args), CMD_N_F);
	return (m_error);
}
