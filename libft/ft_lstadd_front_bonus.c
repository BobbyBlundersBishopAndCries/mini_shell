/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:35:41 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/28 11:56:23 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new -> next = *lst;
	*lst = new;
}
/*int main ()
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
	free(lst);
	return(0);
}*/
