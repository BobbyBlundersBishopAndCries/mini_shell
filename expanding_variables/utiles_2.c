/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:45:42 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/20 13:45:44 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	constr_pd(t_pd *p, t_lst_hk *x, char *str)
{
	p->s = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), x);
	p->i = 0;
	p->s_q = false;
	p->d_q = false;
	p->j = 0;
}

char	*process_del(char *str, t_lst_hk *x)
{
	t_pd	q;

	constr_pd(&q, x, str);
	while (str[q.i])
	{
		if (str[q.i] == '\'')
			q.s_q = !q.s_q;
		if (str[q.i] == '"')
			q.d_q = !q.d_q;
		if (str[q.i] == '$' && (!q.d_q && !q.s_q) && (str[q.i + 1] == '\''
				|| str[q.i + 1] == '"'))
			q.i++;
		q.s[q.j] = str[q.i];
		q.i++;
		q.j++;
	}
	q.s[q.j] = '\0';
	return (q.s);
}
