/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:26:56 by feedback          #+#    #+#             */
/*   Updated: 2025/07/11 11:38:22 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	get_all_argscmd(t_token *token)
{
	size_t	count;
	t_token	*prev;

	prev = NULL;
	count = 0;
	while (token && token->type != PIPE)
	{
		if (prev && !is_redir(prev) && token->type == WORD)
			count++;
		prev = token;
		token = token->next;
	}
	return (count);
}

t_redir	*add_in_file(t_token *redir, t_token *file, t_redir *head, t_lst_hk *x)
{
	t_redir	*r;
	t_redir	*tmp;

	r = ft_malloc(sizeof(t_redir), x);
	r->files = ft_strdump(file->token, x);
	if (redir->type == REDIR_APPEND)
		r->index = R_APPEND;
	else if (redir->type == REDIR_IN)
		r->index = R_IN;
	else if (redir->type == REDIR_OUT)
		r->index = R_OUT;
	else if (redir->type == HEREDOC)
		r->index = R_HEREDOC;
	r->next = NULL;
	r->deja_quoted = file->deja_quoted;
	if (!head)
		head = r;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = r;
	}
	return (head);
}

void	fill_struct_init(t_init_fill *init, t_lst_token *lst_token, t_lst_hk *x)
{
	init->lst_cmds = ft_malloc(sizeof(t_lst_cmd), x);
	init->lst_cmds->head = NULL;
	init->token = lst_token->head;
	init->cmd = NULL;
	init->tail = NULL;
}

t_lst_cmd	*fill_struct(t_lst_token *lst_token, t_lst_hk *x, t_env *env)
{
	t_init_fill	*init;

	init = ft_malloc(sizeof(t_init_fill), x);
	fill_struct_init(init, lst_token, x);
	while (init->token)
	{
		init->cmd = get_cmd(&init->token, x, env);
		if (!init->lst_cmds->head)
		{
			init->lst_cmds->head = init->cmd;
			init->tail = init->cmd;
		}
		else
		{
			init->tail->next = init->cmd;
			init->tail = init->cmd;
		}
		if (init->token && init->token->type == PIPE)
			init->token = init->token->next;
	}
	return (init->lst_cmds);
}
