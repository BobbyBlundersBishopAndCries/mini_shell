/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_alloc_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:24:42 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/01 17:13:49 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	addadrs_back(void *addrs, t_lst_hk *list)
{
	t_housekept	*new;
	t_housekept	*current;

	if (!list)
		return (0);
	new = malloc(sizeof(t_housekept));
	if (!new)
	{
		ft_printf(2, "ERROR: malloc failed in addadrs_back");
		return (0);
	}
	new->addrs = addrs;
	new->next = NULL;
	if (!list->head)
	{
		list->head = new;
		return (1);
	}
	current = list->head;
	while (current->next)
		current = current->next;
	current->next = new;
	return (1);
}

void	*ft_malloc(size_t size, t_lst_hk *k)
{
	void	*add;

	add = malloc(size);
	if (!add)
	{
		ft_printf(2, "malloc failed in ft_malloc");
		free_all(k);
		exit(1);
	}
	if (!addadrs_back(add, k))
	{
		ft_printf(2, "ERROR");
		free_all(k);
		exit(1);
	}
	return (add);
}

void	free_all(t_lst_hk *k)
{
	t_housekept	*gc;
	t_housekept	*tmp;

	if (!k)
		return ;
	gc = k->head;
	while (gc)
	{
		tmp = gc->next;
		free(gc->addrs);
		free(gc);
		gc = tmp;
	}
	free(k);
	gc = NULL;
}
