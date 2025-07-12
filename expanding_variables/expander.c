/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:07:48 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/11 11:35:31 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_dollar(char *str, t_exstrct *q, t_lst_hk *x, t_env *env,
		int g_es)
{
	char	*val;
	size_t	var_len;

	var_len = 0;
	while (str[q->i + var_len] && (ft_isalnum(str[q->i + var_len]) || str[q->i
			+ var_len] == '_'))
		var_len++;
	if (var_len > 0)
	{
		val = change_value(str + q->i, var_len, x, env);
		q->res = ft_join(q->res, val, x);
		q->i += var_len;
	}
	else if (str[q->i] && !q->in_d)
	{
		if (str[q->i] == '?')
			val = ft_itoa(g_es);
		else
			val = change_value(str + q->i, 1, x, env);
		q->res = ft_join(q->res, val, x);
		q->i++;
	}
	else
		q->res = ft_join(q->res, ft_strdump("$", x), x);
}

static void	constr(t_exstrct *q, t_lst_hk *x)
{
	q->i = 0;
	q->in_d = false;
	q->in_s = false;
	q->res = ft_strdump("", x);
}

char	*string_expander(char *str, t_lst_hk *x, t_type a, t_env *env, int g_es)
{
	t_exstrct	q;

	constr(&q, x);
	while (str[q.i])
	{
		if (str[q.i] == '\'' && !q.in_d)
			q.in_s = !q.in_s;
		else if (str[q.i] == '"' && !q.in_s)
			q.in_d = !q.in_d;
		else if (str[q.i] == '$' && !q.in_s && a != HEREDOC)
		{
			q.i++;
			handle_dollar(str, &q, x, env, g_es);
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
void check_if_heredocquoted(t_lst_token *token)
{
	t_lst_token *tmp;
	t_token *m;
	t_token *curr;
	t_token *prev;

	curr = NULL;
	prev = NULL;
	tmp = token;
	curr = tmp->head;
	prev = curr;
	curr = curr->next;
	m = tmp->head;
	while(m)
	{
		m->deja_quoted = false;
		m = m->next;
	}
	while (curr)
	{
		if (is_redir(prev))
		{
			char *t = curr->token;
			int size = 0;
			while(t[size])
			{
				if(t[size] == '\'' || t[size] == '"')
				{
					curr->deja_quoted = true;
					break;
				}
				size++;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}
void	expander(t_lst_token *token, t_lst_hk *x, t_env *env, int g_es)
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
			curr->token = string_expander(raw, x, 0, env, g_es);
		else
			curr->token = string_expander(raw, x, prev->type, env, g_es);
		prev = curr;
		curr = curr->next;
	}
}
