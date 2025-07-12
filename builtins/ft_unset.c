/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:08:44 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/06 11:35:58 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_node(t_env *node)
{
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

static int	del_arg(t_env **head, char *key)
{
	t_env	*curr;
	t_env	*previous;

	curr = *head;
	previous = NULL;
	if (head == NULL || *head == NULL || !key)
		return (0);
	while (curr)
	{
		if (ft_strcmp(key, curr->key) == 0)
		{
			if (previous)
				previous->next = curr->next;
			else
				*head = (*head)->next;
			free_node(curr);
			return (1);
		}
		previous = curr;
		curr = curr->next;
	}
	return (0);
}

int	ft_unset(t_cmd *cmd)
{
	int	i;
	int	ac;

	if (!cmd || !cmd->env || !(*cmd->env))
		return (1);
	ac = arg_count(cmd->args);
	if (ac == 1)
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			ft_printf(2, "bash: unset `%s\': not a valid identifier\n",
				cmd->args[i]);
			return (1);
		}
		del_arg(cmd->env, cmd->args[i]);
		i++;
	}
	return (0);
}
