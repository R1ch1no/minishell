/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:17:37 by qtran             #+#    #+#             */
/*   Updated: 2022/10/25 18:40:41 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* use lst instead of creating a ptr? since u dont return the pointer anyway? */
/* if lst is used and not ptr does it changed the pointer if its not returned */
int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*ptr;

	if (!lst)
		return (0);
	len = 0;
	ptr = lst;
	while (ptr != NULL)
	{
		len++;
		ptr = ptr->next;
	}
	return (len);
}
