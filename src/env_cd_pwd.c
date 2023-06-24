#include "../minishell.h"

int	cd_home(t_data *data, int i, int found)
{
	char	*home;
	int		x;

	x = -1;
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
	int		i;
	int		found;
	char	**args;

	i = 0;
	found = 0;
	args = malloc((arg_num(*node) + 1) * sizeof(char *));
	if (!args || args == NULL)
		return (write(2, "CD allocation error\n", 20) && 1);
	fill_args(*node, &args);
	if (args[0] == NULL)
		cd_home(data, i, found);
	else
	{
		if (args[1] != NULL)
		{
			ft_putstr_fd("too many argumens\n", 2);
			free_2d_str_arr(&args);
			return (0);
		}
		if (chdir((*node)->cmd) != 0)
			perror(NULL);
	}
	free_2d_str_arr(&args);
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
