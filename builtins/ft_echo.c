/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:42:34 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/20 13:42:36 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_n_flag(const char *s)
{
	int	i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (arg_count(cmd->args) == 1)
	{
		ft_printf(STDOUT_FILENO, "\n");
		return (0);
	}
	while (cmd->args[i] && is_valid_n_flag(cmd->args[i]))
	{
		option = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_printf(STDOUT_FILENO, "%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(STDOUT_FILENO, " ");
		i++;
	}
	if (!option)
		ft_printf(STDOUT_FILENO, "\n");
	return (0);
}
