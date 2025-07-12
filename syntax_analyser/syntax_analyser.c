/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:33:31 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/03 20:50:00 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	newline_error(void)
{
	ft_printf(2, "minishell: syntax error near unexpected token `newline'\n");
	return (0);
}

int	sepipe_o(t_lst_token *token)
{
	t_token	*curr;

	curr = token->head;
	if (curr->type == PIPE)
		return (pipe_error());
	while (curr->next && curr)
	{
		if (curr->type == PIPE && curr->next->type == PIPE)
			return (pipe_error());
		curr = curr->next;
	}
	if (curr->type == PIPE)
		return (pipe_error());
	return (1);
}

bool	is_redir(t_token *a)
{
	if (!a)
		return (false);
	return (a->type == REDIR_APPEND || a->type == REDIR_IN
		|| a->type == REDIR_OUT || a->type == HEREDOC);
}

int	seredir_handle(t_lst_token *token)
{
	t_token	*curr;

	curr = token->head;
	while (curr && curr->next)
	{
		if (is_redir(curr))
		{
			if (is_redir((curr->next)))
				return (redir_error(curr->next->token));
			if (curr->next->type == PIPE)
			{
				if (curr->next->next)
					return (pipe_error());
				else
					return (newline_error());
			}
		}
		curr = curr->next;
	}
	if (is_redir(curr))
		return (newline_error());
	return (1);
}

int	syntax_analyser(t_lst_token *token)
{
	if (!sequotes_handle(token) || !sepipe_o(token) || !seredir_handle(token))
		return (2);
	return (1);
}
