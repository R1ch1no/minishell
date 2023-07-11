/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:18:35 by qtran             #+#    #+#             */
/*   Updated: 2022/10/29 16:29:41 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* *lst = NULL; */

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*following;

	current = *lst;
	while (current)
	{
		following = current->next;
		ft_lstdelone(current, del);
		current = following;
	}
	*lst = NULL;
}

/* void	print_data(t_list *head)
{
	t_list	*ptr;

	if (!head)
		printf("Linked list empty");
	ptr = NULL;
	ptr = head;
	while (ptr)
	{
		printf("%i\n", *(int *)ptr->content);
		ptr = ptr->next;
	}
}

int main ()
{
	int		i1;
	int		i2;
	int		i3;
	t_list	*n1;
	t_list	*n2;
	t_list	*n3;

	i1 = 10;
	i2 = 20;
	i3 = 30;
	n1 = ft_lstnew(&i1);
	n2 = ft_lstnew(&i2);
	n3 = ft_lstnew(&i3);
	ft_lstadd_front(&n1, n2);
	ft_lstadd_front(&n2, n3);
	printf("\n-------------------\n");
	print_data(n3);

	ft_lstclear(t_list **lst, void (*del)(void *))
} */