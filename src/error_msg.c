/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:26:50 by qtran             #+#    #+#             */
/*   Updated: 2023/05/26 14:48:36 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *str)
{
	printf("%s: command not found\n", str);
	//if (< || << || > || >> als letztes)
	printf("bash: syntax error near unexpected token `newline\n");
}
