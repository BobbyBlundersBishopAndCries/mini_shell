/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_snd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:28:15 by feedback          #+#    #+#             */
/*   Updated: 2025/07/17 16:28:15 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_argex(t_h q)
{
	free(q.key);
	free(q.val);
}

static void	handle_new_export(t_env **env, char *arg)
{
	addback_node(env, arg);
	sort_list(*env);
}

void	export_argument(t_env **env, char *arg)
{
	t_h	q;

	if (!arg || !is_valid_identifier(arg))
	{
		ft_printf(2, "minishell: export: `%s`: not a valid identifier\n", arg);
		return ;
	}
	q.eq = ft_strchr(arg, '=');
	if (!q.eq)
	{
		q.existing = find_env_node(*env, arg);
		if (!q.existing)
			handle_new_export(env, arg);
		return ;
	}
	q.key = ft_substr(arg, 0, q.eq - arg);
	q.val = ft_strdup(q.eq + 1);
	if (!q.key || !q.val)
		return ;
	q.existing = find_env_node(*env, q.key);
	if (q.existing)
		update_env_value(q.existing, q.val);
	else
		handle_new_export(env, arg);
	free_argex(q);
}
