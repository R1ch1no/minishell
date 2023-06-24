
#include "../minishell.h"

int	is_num(char *argv)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if ((argv[i] < '0' || argv[i] > '9'))
			if (argv[i] != '+' && argv[i] != '-')
				return (1);
	}
	return (0);
}

void	ft_exit(t_node *node, t_data *data)
{
	int		num;
	char	**args;

	args = malloc((arg_num(node) + 1) * sizeof(char *));
	if (!args || args == NULL)
	{
		write(2, "CD allocation error\n", 20);
		return ;
	}
	fill_args(node, &args);
	if (args[0] == NULL)
	{
		free_2d_str_arr(&args);
		exit(0);
	}
	else if (args[1] != NULL)
	{
		ft_putstr_fd("too many argumens\n", 2);
		free_2d_str_arr(&args);
		return ;
	}
	if (is_num(node->cmd) == 0)
	{
		num = ft_atoi(node->cmd);
		cleanse(data);
		ft_putstr_fd("exit\n", 1);
		free_2d_str_arr(&args);
		exit(num);
	}
	free_2d_str_arr(&args);
	ft_putstr_fd("numeric argument required\n", 2);
}
