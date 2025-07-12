/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:30:13 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/06 11:45:45 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_cmd *cmd)
{
	t_env	*curr;

	curr = *(cmd->env);
	while (curr)
	{
		if (curr->value)
			ft_printf(STDOUT_FILENO, "%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	return (0);
}
