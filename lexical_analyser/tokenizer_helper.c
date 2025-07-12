/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:31:41 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/01 17:15:12 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*get_pipe(int *position, t_lst_hk *x)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), x);
	new->token = ft_strdump("|", x);
	new->type = PIPE;
	new->next = NULL;
	(*position)++;
	return (new);
}

t_token	*get_redir_in_here(char *string, int *position, t_lst_hk *x)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), x);
	new->next = NULL;
	if (string[*position + 1] == '<')
	{
		new->token = ft_strdump("<<", x);
		new->type = HEREDOC;
		*position += 2;
	}
	else
	{
		new->token = ft_strdump("<", x);
		new->type = REDIR_IN;
		(*position)++;
	}
	return (new);
}

t_token	*get_redir_out_append(char *string, int *position, t_lst_hk *x)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), x);
	new->next = NULL;
	if (string[*position + 1] == '>')
	{
		new->token = ft_strdump(">>", x);
		new->type = REDIR_APPEND;
		*position += 2;
	}
	else
	{
		new->token = ft_strdump(">", x);
		new->type = REDIR_OUT;
		(*position)++;
	}
	return (new);
}

t_token	*get_random_wrd(char *string, int *position, t_lst_hk *x)
{
	t_token	*new;
	bool	in_s;
	bool	in_d;

	int (i), (start);
	start = *position;
	in_s = false;
	in_d = false;
	i = *position - 1;
	while (string[++i])
	{
		if (string[i] == '"' && !in_s)
			in_d = !in_d;
		else if (string[i] == '\'' && !in_d)
			in_s = !in_s;
		else if (!in_s && !in_d && (isspace(string[i]) || is_op(string[i])))
			break ;
	}
	new = ft_malloc(sizeof(t_token), x);
	new->token = ft_malloc(sizeof(char) * (i - start + 1), x);
	append_string(new->token, string + start, i - start);
	new->type = WORD;
	new->next = NULL;
	*position = i;
	return (new);
}
