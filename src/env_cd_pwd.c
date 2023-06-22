#include "../minishell.h"

int	cd_home(t_data *data, int x, int i, int found)
{
	char	*home;

	while (data->env_copy[++x])
	{
		if (ft_strcmp_v2_until("HOME=", data->env_copy[x], '=') == 0)
		{
			found = 1;
			break ;
		}
	}
	if (found == 0)
		return (write(1, "cd: HOME not set\n", 17) && 0);
	while (data->env_copy[x][i] != '=')
		i++;
	home = malloc(ft_strlen(&data->env_copy[x][i + 1]) + 1);
	if (!home || home == NULL)
		return (ft_putstr_fd("cd alloc problem !\n", 2), 1);
	ft_strlcpy(home, &data->env_copy[x][i + 1], ft_strlen(&data->env_copy[x][i
			+ 1]) + 1);
	if (chdir(home) != 0)
		perror(NULL);
	free(home);
	return (0);
}

int	ft_cd(t_node **node, t_data *data)
{
	int		x;
	int		i;
	int		found;

	x = -1;
	i = 0;
	found = 0;
	if ((*node) == NULL)
	{
		cd_home(data, x, i, found);
	}
	else if (chdir((*node)->cmd) != 0)
		perror(NULL);
	return (0);
}

int	ft_pwd(void)
{
	char	dir[500000];

	if (getcwd(dir, sizeof(dir)) == NULL)
		perror(NULL);
	else
		printf("%s\n", dir);
	return (0);
}

//dunno how to implement it or when :
//if the command is for example - env HELLO="HELLO"
//env prints the env and HELLO="HELLO" at the end
//but it is not saved in env
int	ft_env(char **env)
{
	print_str_arr(env);
	return (0);
}

int	get_arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (-1);
	while (arr[i])
		i++;
	return (i);
}
