
#include "../minishell.h"

char	*mine_strjoin(char *str1, char *str2, int no)
{
	char	*jstr;
	int		i;
	int		j;

	if (!str1 || str1 == NULL || !str2 || str2 == NULL)
		return (NULL);
	jstr = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2))
			+ 1);
	if (!jstr || jstr == NULL)
		return (NULL);
	j = 0;
	i = -1;
	while (str1[++i])
		jstr[i] = str1[i];
	while (str2[j])
		jstr[i++] = str2[j++];
	jstr[i] = '\0';
	if (no == 1)
		free(str1);
	return (jstr);
}

int	find_index(t_data *data, char *str)
{
	int x;
	int match;

	x = -1;
	match = -1;
	while (data->env_copy[++x])
	{
		if (ft_strcmp_v2_until(str, data->env_copy[x], '=') == 0)
		{
			match = x;
			return (match);
		}
	}
	return (match);
}

int	pwd_change(t_data *data, int x, int pwd, char *variable)
{
	char	*path;
	char	*pwdd;
	int		i;

	i = 0;
	while (data->env_copy[x][i] != '=')
		i++;
	path = malloc(ft_strlen(&data->env_copy[x][i + 1]) + 1);
	if (!path || path == NULL)
		return (malloc_error(data), 1);
	ft_strlcpy(path, &data->env_copy[x][i + 1], ft_strlen(&data->env_copy[x][i
			+ 1]) + 1);
	pwdd = ft_strjoin(variable, path);
	free(data->env_copy[pwd]);
	data->env_copy[pwd] = pwdd;
	free(path);
	return (0);
}

int	pwd_change_two(t_data *data, char *arg, int pwd, char *variable)
{
	DIR		*dirr;
	char	directory[500000];
	char	*pwdd;
	int		i;

	i = 0;
	if (getcwd(directory, sizeof(directory)) == NULL)
		return (0);
	pwdd = mine_strjoin(variable, directory, 1);
	pwdd = mine_strjoin(pwdd, "/", 0);
	pwdd = mine_strjoin(pwdd, arg, 0);
	dirr = opendir(arg);
	if (dirr != NULL)
	{
		closedir(dirr);
		free(data->env_copy[pwd]);
		data->env_copy[pwd] = pwdd;
	}
	else
		free(pwdd);
	return (0);
}

void	ft_pwd_env(t_data *data, char ***args)
{
	int		pwd;
	int		old_pwd;
	int		home;

	pwd = find_index(data, "PWD=");
	old_pwd = find_index(data, "OLDPWD=");
	home = find_index(data, "HOME=");
	if ((*args)[1] == NULL)
	{
		if(pwd != -1 && old_pwd != -1)
			pwd_change(data, pwd, old_pwd, "OLDPWD=");
		if(home != -1 && pwd != -1)
			pwd_change(data, home, pwd, "PWD=");
		return ;
	}
	if ((*args)[2] != NULL)
		return ;
	if (ft_strcmp_v2_until("..", (*args)[1], '\0') == 0)
	{
		if(pwd != -1 && old_pwd != -1)
			pwd_change(data, old_pwd, pwd, "PWD=");
		return ;
	}
	if(pwd != -1 && old_pwd != -1)
		pwd_change(data, pwd, old_pwd, "OLDPWD=");
	if(home != -1 && pwd != -1)
		pwd_change_two(data, (*args)[1], pwd, "PWD=");
}







