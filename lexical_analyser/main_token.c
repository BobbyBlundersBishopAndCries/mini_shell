/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:45:49 by feedback          #+#    #+#             */
/*   Updated: 2025/07/09 18:45:50 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_op(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\0');
}

static int	tokenizer_init(t_help *q, t_lst_hk *x, char *str)
{
	q->token = ft_malloc(sizeof(t_lst_token), x);
	if (!q->token)
		return (0);
	q->token->head = NULL;
	q->tail = NULL;
	q->i = 0;
	if (str[0] == '\0')
	{
		q->new = ft_malloc(sizeof(t_token), x);
		if (!q->new)
			return (0);
		q->new->token = ft_strdump("", x);
		q->new->type = WORD;
		q->new->next = NULL;
		q->token->head = q->new;
	}
	return (1);
}

t_lst_token	*tokenizer(char *str, t_lst_hk *x)
{
	t_help	q;

	if (!tokenizer_init(&q, x, str))
		return (NULL);
	while (str[q.i])
	{
		while (str[q.i] && isspace(str[q.i]))
			q.i++;
		if (str[q.i] == '|')
			q.new = get_pipe(&q.i, x);
		else if (str[q.i] == '<')
			q.new = get_redir_in_here(str, &q.i, x);
		else if (str[q.i] == '>')
			q.new = get_redir_out_append(str, &q.i, x);
		else
			q.new = get_random_wrd(str, &q.i, x);
		if (!q.new)
			return (NULL);
		if (!q.token->head)
			q.token->head = q.new;
		else
			q.tail->next = q.new;
		q.tail = q.new;
	}
	return (q.token);
}
