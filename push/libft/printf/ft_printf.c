/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:31:57 by qtran             #+#    #+#             */
/*   Updated: 2023/02/25 15:04:59 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	typecheck(va_list args, const char *str, int len)
{
	if (*str == 'c')
		len += len_putchar(va_arg(args, int));
	else if (*str == 's')
		len += len_putstr(va_arg(args, char *));
	else if (*str == 'p')
		len += ft_pointer((unsigned long long)va_arg(args, void *));
	else if (*str == 'i' || *str == 'd')
		len += len_itoa(va_arg(args, int));
	else if (*str == 'u')
		len += ft_u(va_arg(args, unsigned int));
	else if (*str == 'x')
		len += ft_itohex((unsigned long)va_arg(args, unsigned int), 32);
	else if (*str == 'X')
		len += ft_itohex((unsigned long)va_arg(args, unsigned int), 0);
	else if (*str == '%')
		len += write(1, "%", 1);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	args;

	len = 0;
	if (!str)
		return (len);
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			len = typecheck(args, str, len);
		}
		else
			len += len_putchar(*str);
		str++;
	}
	va_end(args);
	return (len);
}
