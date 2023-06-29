/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_itoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:43:34 by qtran             #+#    #+#             */
/*   Updated: 2022/11/04 18:06:00 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	len_itoa(int i)
{
	char	*str;
	int		len;

	str = printf_itoa(i);
	len = len_putstr(str);
	free(str);
	return (len);
}
