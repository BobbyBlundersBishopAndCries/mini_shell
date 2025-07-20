/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:42:46 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/20 13:42:48 by mlakhdar         ###   ########.fr       */
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
