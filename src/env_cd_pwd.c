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

void	ft_env(char **env)
{
	print_str_arr(env);
}