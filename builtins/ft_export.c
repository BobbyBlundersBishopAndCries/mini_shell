/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:43:20 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/21 18:37:47 by mlakhdar         ###   ########.fr       */
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
				ret = status;
		}
		i++;
	}
	return (ret);
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
