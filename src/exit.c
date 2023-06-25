
#include "../minishell.h"
#include <limits.h>

long long	ft_atoi_exit(const char *str, t_data *data)
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (((result * 10 + (str[i] - '0') * sign) > LLONG_MAX || ((result * 10
						+ (str[i] - '0') * sign) < LLONG_MIN)))
			data->problem = 1;
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

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

int	ft_exit(t_data *data, char ***args)
{
	long long	num;

	if ((*args)[1] == NULL)
	{
		free_2d_str_arr(args);
		exit(0);
	}
	if ((*args)[2] != NULL)
	{
		ft_putstr_fd("too many argumens\n", 2);
		return (free_2d_str_arr(args), 0);
	}
	num = ft_atoi_exit((*args)[1], data);
	if (is_num((*args)[1]) == 0 && data->problem == 0)
	{
		cleanse(data);
		ft_putstr_fd("exit\n", 1);
		free_2d_str_arr(args);
		exit(num);
	}
	free_2d_str_arr(args);
	ft_putstr_fd("numeric argument required\n", 2);
	return (0);
}
