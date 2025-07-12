/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:55:42 by mohabid           #+#    #+#             */
/*   Updated: 2024/11/03 16:00:47 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	void	*func;
	t_list	*result;

	if (!f || !del || !lst)
		return (NULL);
	result = NULL;
	while (lst != NULL)
	{
		func = f(lst->content);
		new_node = ft_lstnew(func);
		if (new_node == NULL)
		{
			if (func)
				del(func);
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, new_node);
		lst = lst -> next;
	}
	return (result);
}
