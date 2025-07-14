/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:54:21 by med               #+#    #+#             */
/*   Updated: 2025/07/14 20:10:51 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_new_export(t_env **env, char *arg)
{
	addback_node(env, arg);
	sort_list(*env);
}

static void	export_argument(t_env **env, char *arg)
{
	char	*eq;
	char	*key;
	char	*val;
	t_env	*existing;

	if (!arg || !is_valid_identifier(arg))
	{
		ft_printf(2, "minishell: export: `%s`: not a valid identifier\n",
			arg ? arg : "(null)");
		return ;
	}
	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		existing = find_env_node(*env, arg);
		if (!existing)
			handle_new_export(env, arg);
		return ;
	}
	key = ft_substr(arg, 0, eq - arg);
	val = ft_strdup(eq + 1);
	if (!key || !val)
		return ;
	existing = find_env_node(*env, key);
	if (existing)
		update_env_value(existing, val);
	else
		handle_new_export(env, arg);
	free(key);
	free(val);
}

static int	count_non_empty_args(char **args)
{
	int	i = 1;
	int	count = 0;

	while (args[i])
	{
		if (args[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

static void	export_with_args(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '\0')
			export_argument(cmd->env, cmd->args[i]);
		i++;
	}
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
			printf("\n");
			curr = curr->next;
		}
	}
	else
		export_with_args(cmd);
	return (0);
}
