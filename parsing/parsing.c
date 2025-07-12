/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:46:15 by feedback          #+#    #+#             */
/*   Updated: 2025/07/09 18:46:16 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst_cmd	*parsing(char *input, t_env *env, int *g_es)
{
	t_lst_hk	*x;
	t_lst_token	*lst_token;
	t_lst_cmd	*lst;

	x = malloc(sizeof(t_lst_hk));
	if (!x)
		return (NULL);
	x->head = NULL;
	trim_space(&input);
	lst_token = tokenizer(input, x);
	if ((!lst_token || !lst_token->head) || syntax_analyser(lst_token) == 2)
	{
		*g_es = 2;
		free_all(x);
		return (NULL);
	}
	expander(lst_token, x, env, *g_es);
	lst = fill_struct(lst_token, x, env);
	lst->k = x;
	return (lst);
}
