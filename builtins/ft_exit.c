/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:35:36 by med               #+#    #+#             */
/*   Updated: 2025/07/09 13:51:30 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	valid_error(char *arg)
{
	ft_printf(2, "exit\n");
	ft_printf(2, "bash: exit: %s: numeric argument required\n", arg);
	exit(2);
}

int	ft_exit(t_cmd *cmd)
{
	int	exit_status;
	int	count;

	count = arg_count(cmd->args);
	exit_status = 0;
	if (count > 2)
	{
		ft_printf(2, "exit\nbash: exit: too many arguments\n");
		return (1);
	}
	if (cmd->args[1])
	{
		if (!is_valid_number(cmd->args[1]))
			valid_error(cmd->args[1]);
		exit_status = (unsigned char)ft_atoi(cmd->args[1]);
	}
	else
		exit_status = g_shell.exit_status;
	exit(exit_status);
}
