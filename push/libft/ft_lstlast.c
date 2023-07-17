/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:17:56 by qtran             #+#    #+#             */
/*   Updated: 2022/10/25 19:56:22 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

/* void print_data(t_list *head)
{
	t_list	*temp;

    if (!head)
        printf("Linked list empty");
    temp = NULL;
    temp = head;
    while (temp != NULL)
    {
        printf("%i\n", *(int*)temp->content);
        temp = temp->next;
    }
}

int	main(void)
{

    t_list n1, n2, n3;
    void *c1, *c2, *c3;

    int cc1 = 11;
    int cc3 = 22;
    int cc2 = 33;

    c1 = &cc1;
    c1 = &cc1;
    c1 = &cc1;

    n1.content = c1;
    n2.content = c2;
    n3.content = c3;
    
    t_list *head = &n1;
    t_list **temp = &head;

    ft_lstadd_front(temp, c2);
    ft_lstadd_front(temp, c3);

    t_list *head3= &n3;

    print_data (head);
    return (0);
} */