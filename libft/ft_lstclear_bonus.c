/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:11:37 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/29 17:30:41 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*address_holder;

	current = *lst;
	if (lst == NULL || current == NULL || del == NULL)
		return ;
	while (current != NULL)
	{
		address_holder = current -> next;
		del(current -> content);
		free(current);
		current = address_holder;
	}
	*lst = NULL;
}
