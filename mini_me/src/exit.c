/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:04:42 by rkurnava          #+#    #+#             */
/*   Updated: 2023/06/30 11:11:08 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	overflow(long long result, char num, int sign, t_data *data)
{
	long long	res;

	res = result * 10 * sign;
	if (res == 9223372036854775800 && num == '8')
	{
		data->problem = 1;
		return (1);
	}
	if (res == -9223372036854775800 && num == '9')
	{
		data->problem = 1;
		return (1);
	}
	return (0);
}

long long	ft_atoi_exit(const char *str, t_data *data)
{
	int			i;
	int			sign;
	long long	result;

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
		if (overflow(result, str[i], sign, data) == 1)
			return (sign * result);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	is_num(char *argv, t_data *data)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if ((argv[i] < '0' || argv[i] > '9'))
		{
			if (argv[i] != '+' && argv[i] != '-')
			{
				data->problem = 1;
				return (1);
			}
		}
	}
	return (0);
}

void	exit_for_exit(t_data *data, char ***args)
{
	free_2d_str_arr(args);
	if (data->problem == 1)
	{
		cleanse(data);
		exit(2);
	}
	else
	{
		cleanse(data);
		exit(1);
	}
}

int	ft_exit(t_data *data, char ***args)
{
	long long	num;

	if ((*args)[1] == NULL)
	{
		free_2d_str_arr(args);
		cleanse(data);
		exit(0);
	}
	if ((*args)[2] != NULL)
	{
		ft_putstr_fd("too many argumens\n", 2);
		exit_for_exit(data, args);
	}
	num = ft_atoi_exit((*args)[1], data);
	if (is_num((*args)[1], data) == 0 && data->problem == 0)
	{
		cleanse(data);
		ft_putstr_fd("exit\n", 1);
		free_2d_str_arr(args);
		exit(num);
	}
	ft_putstr_fd("numeric argument required\n", 2);
	exit_for_exit(data, args);
	return (0);
}
