/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:33:29 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/03 20:38:06 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	constr(t_helpq *q)
{
	q->s = 0;
	q->d = 0;
	q->i = 0;
	q->in_d = false;
	q->in_s = false;
}

int	check_quote(char *string)
{
	t_helpq	q;

	constr(&q);
	while (string[q.i])
	{
		if (string[q.i] == '\"' && !q.in_s)
		{
			q.in_d = !q.in_d;
			q.d++;
		}
		else if (string[q.i] == '\'' && !q.in_d)
		{
			q.in_s = !q.in_s;
			q.s++;
		}
		q.i++;
	}
	if ((q.s % 2 != 0) || (q.d % 2 != 0))
	{
		ft_printf(2, "minishell: unclosed quotes\n");
		return (0);
	}
	return (1);
}

int	sequotes_handle(t_lst_token *token)
{
	t_token	*curr;

	curr = token->head;
	while (curr)
	{
		if (check_quote(curr->token) == 0)
			return (0);
		curr = curr->next;
	}
	return (1);
}

int	redir_error(char *token)
{
	ft_printf(2, "minishell: syntax error near unexpected token `%s'\n", token);
	return (0);
}

int	pipe_error(void)
{
	ft_printf(2, "minishell: syntax error near unexpected token `|'\n");
	return (0);
}
