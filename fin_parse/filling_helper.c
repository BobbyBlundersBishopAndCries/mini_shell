/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:46:08 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/21 18:38:27 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_get_cmd(t_get_cmd_init *init, t_token **t, t_lst_hk *x, t_env *env)
{
	init->token = *t;
	init->index = 0;
	init->count = get_all_argscmd(init->token);
	init->cmd = ft_malloc(sizeof(t_cmd), x);
	init->cmd->args = ft_malloc(sizeof(char *) * (init->count + 2), x);
	init->cmd->files = NULL;
	init->cmd->next = NULL;
	init->cmd->env = &env;
}

t_cmd	*get_cmd(t_token **t, t_lst_hk *x, t_env *env)
{
	t_get_cmd_init	*init;

	init = ft_malloc(sizeof(t_get_cmd_init), x);
	init_get_cmd(init, t, x, env);
	while (init->token && init->token->type != PIPE)
	{
		if (is_redir(init->token) && init->token->next
			&& init->token->next->type == WORD)
		{
			init->cmd->files = add_in_file(init->token, init->token->next,
					init->cmd->files, x);
			init->token = init->token->next;
		}
		else if (init->token->type == WORD)
		{
			if (!init->token->expanded)
				init->cmd->args[init->index++] = ft_strdump(init->token->token,
						x);
		}
		init->token = init->token->next;
	}
	init->cmd->args[init->index] = NULL;
	*t = init->token;
	return (init->cmd);
}
