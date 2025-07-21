/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:44:21 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/21 16:17:06 by feedback         ###   ########.fr       */
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

char	*string_expander(t_ee *ee, t_type a, bool *ok)
{
	t_exstrct(q);
	constr(&q, ee->x);
	if (a == HEREDOC)
		ee->str = process_del(ee->str, ee->x);
	while (ee->str[q.i])
	{
		if (ee->str[q.i] == '\'' && !q.in_d)
			q.in_s = !q.in_s;
		else if (ee->str[q.i] == '"' && !q.in_s)
			q.in_d = !q.in_d;
		else if (ee->str[q.i] == '$' && !q.in_s && a != HEREDOC)
		{
			q.i++;
			handle_dollar(ee->str, &q, ee->x, ee->env);
			if (q.res[0] == '\0')
				*ok = true;
			continue ;
		}
		else
		{
			q.tmp[0] = ee->str[q.i];
			q.tmp[1] = '\0';
			q.res = ft_join(q.res, ft_strdump(q.tmp, ee->x), ee->x);
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
	t_ee	ee;

	t_token *(curr), *(prev);
	curr = token->head;
	prev = NULL;
	ee.x = x;
	ee.env = env;
	ee.str = NULL;
	bool_set(token);
	check_if_heredocquoted(token);
	while (curr)
	{
		ee.str = curr->token;
		if (prev == NULL)
			curr->token = string_expander(&ee, 0, &curr->expanded);
		else
		{
			curr->token = string_expander(&ee, prev->type, &curr->expanded);
		}
		prev = curr;
		curr = curr->next;
	}
}
