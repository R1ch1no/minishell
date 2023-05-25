/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkurnava <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:07:26 by rkurnava          #+#    #+#             */
/*   Updated: 2023/05/25 19:38:03 by rkurnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//just had an idea, but I dont think this works
void	ft_unset(char **env, char *to_unset)
{
	char	*to_change;

	to_change = getenv(to_unset);
	to_change = NULL;
}
