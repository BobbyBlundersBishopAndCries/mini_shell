/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:49:35 by feedback          #+#    #+#             */
/*   Updated: 2025/07/09 18:50:00 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_env_nodes(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void	sort_list(t_env *head)
{
	t_env	*curr;
	t_env	*curr2;

	curr = head;
	while (curr)
	{
		curr2 = curr->next;
		while (curr2)
		{
			if (ft_strcmp(curr->key, curr2->key) > 0)
				swap_env_nodes(curr, curr2);
			curr2 = curr2->next;
		}
		curr = curr->next;
	}
}

t_env	*find_env_node(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	update_env_value(t_env *node, char *value)
{
	if (!node)
		return ;
	free(node->value);
	node->value = ft_strdup(value);
}
