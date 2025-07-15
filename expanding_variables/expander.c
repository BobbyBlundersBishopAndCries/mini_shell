/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:07:48 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/15 20:29:33 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_number_size(int number)
{
	size_t	length;

	length = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		length += 1;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}

char	*ft_ittoa(int n, t_lst_hk *x)
{
	char	*string;
	size_t	length;

	length = ft_number_size(n);
	if (n == -2147483648)
		return (ft_strdump("-2147483648", x));
	string = (char *)ft_malloc(sizeof(char) * length + 1, x);
	if (string == NULL)
		return (NULL);
	if (n < 0)
	{
		string[0] = '-';
		n = -n;
	}
	if (n == 0)
		string[0] = '0';
	string[length] = '\0';
	while (n != 0)
	{
		string[length - 1] = (n % 10) + '0';
		n = n / 10;
		length--;
	}
	return (string);
}

static void	handle_dollar(char *str, t_exstrct *q, t_lst_hk *x, t_env *env)
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
			val = ft_ittoa(g_shell.exit_status, x);
		else
			val = change_value(str + q->i, 1, x, env);
		q->res = ft_join(q->res, val, x);
		if (str[q->i] != '\'' || str[q->i] != '"')
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

char	*process_del(char *str, t_lst_hk *x)
{
	char	*s;
	int		i;
	bool	s_q;
	bool	d_q;
	int		j;

	s = NULL;
	s = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), x);
	i = 0;
	s_q = false;
	d_q = false;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			s_q = !s_q;
		if (str[i] == '"')
			d_q = !d_q;
		if (str[i] == '$' && (!d_q && !s_q) && (str[i + 1] == '\'' || str[i
				+ 1] == '"'))
			i++;
		s[j] = str[i];
		j++;
		i++;
	}
	s[j] = '\0';
	return (s);
}

char	*string_expander(char *str, t_lst_hk *x, t_type a, t_env *env)
{
	t_exstrct	q;

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

void	check_if_heredocquoted(t_lst_token *token)
{
	t_lst_token	*tmp;
	t_token		*m;
	t_token		*curr;
	t_token		*prev;
	char		*t;
	int			size;

	curr = NULL;
	prev = NULL;
	tmp = token;
	curr = tmp->head;
	prev = curr;
	curr = curr->next;
	m = tmp->head;
	while (m)
	{
		m->deja_quoted = false;
		m = m->next;
	}
	while (curr)
	{
		if (is_redir(prev))
		{
			t = curr->token;
			size = 0;
			while (t[size])
			{
				if (t[size] == '\'' || t[size] == '"')
				{
					curr->deja_quoted = true;
					break ;
				}
				size++;
			}
		}
		prev = curr;
		curr = curr->next;
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
