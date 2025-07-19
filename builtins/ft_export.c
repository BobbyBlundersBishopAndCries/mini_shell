/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:54:21 by med               #+#    #+#             */
/*   Updated: 2025/07/17 16:13:14 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_non_empty_args(char **args)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

static int	export_with_args(t_cmd *cmd)
{
	int	i;
	int	status;
	int	ret;

	i = 1;
	ret = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '\0')
		{
			status = export_argument(cmd->env, cmd->args[i]);
			if (status != 0)
				ret = status; // keep failure status if any
		}
		i++;
	}
	return ret;
}

int	ft_export(t_cmd *cmd)
{
	t_env	*curr;

	if (!cmd || !cmd->env)
		return (1);
	if (arg_count(cmd->args) == 1 || count_non_empty_args(cmd->args) == 0)
	{
		sort_list(*cmd->env);
		curr = *cmd->env;
		while (curr)
		{
			printf("declare -x %s", curr->key);
			if (curr->value)
				printf("=\"%s\"", curr->value);
			else
				printf("=\"\"");
			printf("\n");
			curr = curr->next;
		}
	}
	else
		return (export_with_args(cmd));
	return (0);
}
