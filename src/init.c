/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:31:53 by qtran             #+#    #+#             */
/*   Updated: 2023/04/27 15:34:30 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_data(t_data *data, char **env)
{
    data->line_read = NULL;
    data->env_copy = dup_str_arr(env); //must be freed
}