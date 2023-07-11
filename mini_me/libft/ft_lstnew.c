/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:16:55 by qtran             #+#    #+#             */
/*   Updated: 2022/10/24 18:58:30 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*first;

	first = (t_list *)malloc(sizeof(t_list));
	if (!first)
		return (NULL);
	first->content = content;
	first->next = NULL;
	return (first);
}
/* 
//the following is wrong because typedef is used in header file
t_list	*ft_lstnew(void *content)
{
    struct t_list *first;
    first = (struct t_list *)malloc(sizeof(struct t_list));
    first->content = content;
    first ->next = NULL;
    return (first);
} */
