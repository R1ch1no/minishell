/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:45:48 by qtran             #+#    #+#             */
/*   Updated: 2023/06/06 13:48:45 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int	fun(void)
{
	static int	count;

	if (!count)
	{
		count = 50;
	}
	count++;
	return (count);
}

int	main(void)
{
	printf("%d ", fun());
	printf("%d ", fun());
	printf("%d ", fun());
	printf("%d ", fun());
	return (0);
}
