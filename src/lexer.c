/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:38:12 by qtran             #+#    #+#             */
/*   Updated: 2023/05/21 13:41:32 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void lexer(t_data *data)
{
    if (data->line_read == NULL)
        return ; //exit

    //gets rid of all the whitespaces before and after actual cmd line
    if (trim_spaces(data) == 1)
        return ;
    
    data->cmd_line = malloc(sizeof(char *) * (count_tokens_v2(data->line_read) + 1));
    if (data->cmd_line == NULL)
        return (perror("minishell malloc"), cleanup(data));
    init_cmd_line(data);
}

int trim_spaces(t_data *data)
{
    char *temp;
    temp = ft_strtrim(data->line_read, " ");
    if (temp == NULL)
        return (cleanup(data), 1);
    free(data->line_read);
    data->line_read = temp;
    //printf("trimmed spaces succesfully!\n");
    //printf("This is in line_read: (%s)\n", data->line_read);//
    return (0);
}