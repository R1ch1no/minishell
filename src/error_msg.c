/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:26:50 by qtran             #+#    #+#             */
/*   Updated: 2023/05/07 15:04:58 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void error_msg(char *str)
{
    printf("%s: command not found\n", str);
    //if (< || << || > || >> als letztes)
        printf("bash: syntax error near unexpected token `newline\n");
    
}