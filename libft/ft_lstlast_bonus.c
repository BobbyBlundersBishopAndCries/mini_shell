/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:16:29 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/28 12:28:06 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (!current)
		return (NULL);
	while (current -> next != NULL)
		current = current -> next;
	return (current);
}
/*
int main ()
{
	int i = 1;
	int *v = malloc(sizeof(int));
	int *p = malloc(sizeof(int));
	t_list *lst = NULL;
	*v = 42;
	*p = 15;
	t_list *node1 = ft_lstnew(v);
	t_list *node2 = ft_lstnew(p);
	ft_lstadd_front(&lst, node1);
	ft_lstadd_front(&lst, node2);
	t_list *current;
	current = lst;
	while(current != NULL)
	{
		printf("node added %d content %d\n",i,*(int *)(current -> content));
		i++;
		current = current -> next;
	}
	t_list *new = ft_lstlast(lst);
	printf("the content of the last node is %d", *(int *)(new -> content));
	free(lst);
	return(0);
}*/
