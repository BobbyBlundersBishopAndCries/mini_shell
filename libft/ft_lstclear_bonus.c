/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:11:37 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/21 18:39:45 by mlakhdar         ###   ########.fr       */
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
		address_holder = current->next;
		del(current->content);
		free(current);
		current = address_holder;
	}
	*lst = NULL;
}
