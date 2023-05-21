/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:31:53 by qtran             #+#    #+#             */
/*   Updated: 2023/05/21 17:04:12 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_data(t_data *data, char **env)
{
    data->line_read = NULL;
    data->env_copy = dup_str_arr(env); //must be freed; what happens if environment is empty? easy fix or nah?
    data->cmd_line = NULL;
    
    data->fd_infile = -1;
    data->fd_outfile = -1;
}