/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:35:36 by med               #+#    #+#             */
/*   Updated: 2025/07/17 13:19:52 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_digitstr(const char *str)
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

static int	last_digit_overflows(int digit, int sign)
{
	if (sign == 1 && digit > LONG_MAX % 10)
		return (1);
	if (sign == -1 && digit > -(LONG_MIN % 10))
		return (1);
	return (0);
}

static int	is_overflow(const char *str)
{
	unsigned long	result;
	int				sign;
	int				digit;

	result = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (result > LONG_MAX / 10)
			return (1);
		if (result == LONG_MAX / 10 && last_digit_overflows(digit, sign))
			return (1);
		result = result * 10 + digit;
		str++;
	}
	return (0);
}

static void	check_exit_argument(const char *str)
{
	int	is_valid;

	is_valid = 1;
	if (!is_digitstr(str))
		is_valid = 0;
	else if (is_overflow(str))
		is_valid = 0;
	if (!is_valid)
	{
		ft_printf(2, "exit\n");
		ft_printf(2, "minihell: exit: %s: numeric argument required\n", str);
		exit(2);
	}
}

int	ft_exit(t_cmd *cmd   , t_lst_cmd *head)
{
	int	exit_status;
	int	count;

	count = arg_count(cmd->args);
	exit_status = 0;
	if (cmd->args[1])
	{
		check_exit_argument(cmd->args[1]);
		exit_status = (unsigned char)ft_atoi(cmd->args[1]);
	}
	if (count > 2)
	{
		ft_printf(2, "exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	else
		exit_status = g_shell.exit_status;
	ft_printf(1, "exit\n");
		t_cmd *tmp;
	tmp = head->head;
	while (tmp)
	{
		free_array(tmp->envp);
		tmp = tmp->next;
	}

	t_env *env = *head->head->env;
	free_env_list(env);
	free_all(head->k);
	exit(exit_status);
}
