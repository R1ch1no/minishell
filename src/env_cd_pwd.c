#include "../minishell.h"

int	ft_cd(t_node **node)
{
	if ((*node) == NULL)
		return (1);
	if (chdir((*node)->cmd) != 0)
	{
		(*node) = (*node)->next;
		perror(NULL);
		return (1);
	}
	else
		(*node) = (*node)->next;
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

//dunno how to implement it or when :
//if the command is for example - env HELLO="HELLO"
//env prints the env and HELLO="HELLO" at the end
//but it is not saved in env
void	ft_env(char **env, t_node **node)
{
	print_str_arr(env);
	(*node) = (*node)->next;
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
