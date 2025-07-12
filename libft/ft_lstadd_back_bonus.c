/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:04:53 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/31 18:57:12 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		new -> next = NULL;
	}
	else
	{
		while (current -> next != NULL)
			current = current -> next;
		current -> next = new;
	}
}

/*int main ()
{
		int i = 1;
		t_list *lst2 = NULL;
        t_list *lst = NULL;
        ft_lstadd_back(&lst, ft_lstnew((void *)1));
        ft_lstadd_back(&lst,ft_lstnew((void *)2));
        ft_lstadd_back(&lst2, ft_lstnew((void *)3));
        ft_lstadd_back(&lst2,ft_lstnew((void *)4));	
        ft_lstadd_back(&lst,lst2);
        t_list *current;
        current = lst;
        while(current != NULL)
        {
           printf("node added %d content %d\n",i,(int)(current -> content));
           current = current -> next;
		   i++;
        }
        free(lst);
        return(0);
}*/
