/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:45:32 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/21 12:23:24 by feedback         ###   ########.fr       */
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

void	bool_set(t_lst_token *token)
{
	t_token	*t;

	t = token->head;
	while (t)
	{
		t->expanded = false;
		t = t->next;
	}
}

void	handle_dollar(char *str, t_exstrct *q, t_lst_hk *x, t_env *env)
{
	char *(val);
	size_t(var_len);
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
