/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:07:48 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/18 15:15:52 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	constr(t_exstrct *q, t_lst_hk *x)
{
	q->i = 0;
	q->in_d = false;
	q->in_s = false;
	q->res = ft_strdump("", x);
}

char	*string_expander(char *str, t_lst_hk *x, t_type a, t_env *env)
{
	t_exstrct (q);
	constr(&q, x);
	if (a == HEREDOC)
		str = process_del(str, x);
	while (str[q.i])
	{
		if (str[q.i] == '\'' && !q.in_d)
			q.in_s = !q.in_s;
		else if (str[q.i] == '"' && !q.in_s)
			q.in_d = !q.in_d;
		else if (str[q.i] == '$' && !q.in_s && a != HEREDOC)
		{
			q.i++;
			handle_dollar(str, &q, x, env);
			continue ;
		}
		else
		{
			q.tmp[0] = str[q.i];
			q.tmp[1] = '\0';
			q.res = ft_join(q.res, ft_strdump(q.tmp, x), x);
		}
		q.i++;
	}
	return (q.res);
}

void	constr_cih(t_cih *cih, t_lst_token *token)
{
	cih->curr = NULL;
	cih->prev = NULL;
	cih->tmp = token;
	cih->curr = cih->tmp->head;
	cih->prev = cih->curr;
	cih->curr = cih->curr->next;
	cih->m = cih->tmp->head;
	while (cih->m)
	{
		cih->m->deja_quoted = false;
		cih->m = cih->m->next;
	}
}

void	check_if_heredocquoted(t_lst_token *token)
{
	t_cih	q;

	constr_cih(&q, token);
	while (q.curr)
	{
		if (is_redir(q.prev))
		{
			q.t = q.curr->token;
			q.size = 0;
			while (q.t[q.size])
			{
				if (q.t[q.size] == '\'' || q.t[q.size] == '"')
				{
					q.curr->deja_quoted = true;
					break ;
				}
				q.size++;
			}
		}
		q.prev = q.curr;
		q.curr = q.curr->next;
	}
}

void	expander(t_lst_token *token, t_lst_hk *x, t_env *env)
{
	t_token	*curr;
	t_token	*prev;
	char	*raw;

	curr = token->head;
	prev = NULL;
	raw = NULL;
	check_if_heredocquoted(token);
	while (curr)
	{
		raw = curr->token;
		if (prev == NULL)
			curr->token = string_expander(raw, x, 0, env);
		else
			curr->token = string_expander(raw, x, prev->type, env);
		prev = curr;
		curr = curr->next;
	}
}
