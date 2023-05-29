
#include "../minishell.h"

int	ft_cd(const char *path)
{
	if (!path)
		return (1);
	if (path[0] == '\0')
		return (1);
	if (chdir(path) != 0)
	{
		perror(NULL);
		return (1);
	}
	return (0);
}

void	ft_pwd(void)
{
	char	dir[500000];

	if (getcwd(dir, sizeof(dir)) == NULL)
		perror(NULL);
	else
		printf("%s\n", dir);
}

void	ft_echo(const char *str, int n)
{
	int	i;

	i = 0;
	if ((!str || str == NULL) && n == 1)
		return ;
	if ((!str || str == NULL) && n == 0)
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

void	ft_env(char **env)
{
	print_str_arr(env);
}

void	ft_unset(char **env, char *search)
{
	int		y;
	int		z;
	int		x;
	char	**new_env;

	y = 0;
	z = -1;
	while (env[y])
		y++;
	new_env = malloc((y + 1) * sizeof(char *));
	y = -1;
	while (env[++y])
	{
		x = 0;
		while (search[x] && env[y][x] && search[x] == env[y][x])
		{
			if (search[x] == env[y][x] && search[x + 1] == '\0')
				y++;
			x++;
		}
		if (env[y])
		{
			new_env[++z] = malloc(ft_strlen(env[y]) + 1);
			ft_strlcpy(new_env[z], env[y], ft_strlen(env[y]) + 1);
		}
	}
	y = -1;
	new_env[z + 1] = NULL;
	*(&env) = new_env;
}
