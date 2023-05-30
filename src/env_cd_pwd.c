#include "../minishell.h"

int	ft_cd(t_node *node)
{
	if (node == NULL)
		return (1);
	if (node->cmd[0] == '\0')
		return (1);
	if (chdir(node->cmd) != 0)
	{
		perror(NULL);
		return (1);
	}
	node = node->next;
	return (0);
}

void	ft_pwd(t_node *node)
{
	char	dir[500000];

	if (getcwd(dir, sizeof(dir)) == NULL)
		perror(NULL);
	else
		printf("%s\n", dir);
	node = node->next;
}

void	ft_env(char **env, t_node *node)
{
	print_str_arr(env);
	node = node->next;
}
