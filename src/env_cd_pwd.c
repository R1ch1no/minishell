#include "../minishell.h"

int	ft_cd(t_node **node)
{
	if ((*node) == NULL)
		return (0);
	if (chdir((*node)->cmd) != 0)
	{
		perror(NULL);
		return (0);
	}
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
