
#include "../minishell.h"

int	find_index(t_data *data, char *str)
{
	int x;
	int match;

	x = -1;
	match = -1;
	printf("finx_index str : %s\n", str);
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
	DIR		*dir;
	char	directory[500000];
	char	*pwdd;
	int		i;

	i = 0;
	if (getcwd(directory, sizeof(dir)) == NULL)
		return (0);
	printf("directory : %s\n", directory);
	pwdd = ft_strjoin(variable, directory);
	pwdd = ft_strjoin(pwdd, "/");
	pwdd = ft_strjoin(pwdd, arg);
	printf("pwdd : %s\n", pwdd);
	dir = opendir(arg);
	if (dir != NULL)
	{
		closedir(dir);
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
	printf("pwd : %d old_pwd : %d home :%d\n", pwd, old_pwd, home);
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







