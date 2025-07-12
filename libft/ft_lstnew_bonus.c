/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:47:44 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/28 11:34:15 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new -> content = content;
	new -> next = NULL;
	return (new);
}
/*int main()
{
    int *value = (int *)malloc(sizeof(int));
    *value = 42;
    t_list *node = ft_lstnew(value);
    printf("Node content: %d\n",*(int *)(node->content));
    free(node);

    return 0;
}*/
