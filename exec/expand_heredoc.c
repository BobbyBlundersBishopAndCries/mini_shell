/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:18:38 by feedback          #+#    #+#             */
/*   Updated: 2025/07/17 16:18:49 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*str_append(char *dst, const char *src)
{
	size_t	len_dst;
	size_t	len_src;
	char	*res;

	if (!src)
		return (dst);
	if (!dst)
		return (strdup(src));
	len_dst = strlen(dst);
	len_src = strlen(src);
	res = malloc(len_dst + len_src + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, dst, len_dst);
	ft_memcpy(res + len_dst, src, len_src);
	res[len_dst + len_src] = '\0';
	free(dst);
	return (res);
}

static char	*get_word(const char *word, int size)
{
	char	*w;

	w = malloc(size + 1);
	if (!w)
		return (NULL);
	memcpy(w, word, size);
	w[size] = '\0';
	return (w);
}

static char	*nor_word(const char *line, int i, char *result)
{
	int		start;
	char	*chunk;

	start = i;
	chunk = NULL;
	while (line[i] && line[i] != '$')
		i++;
	chunk = get_word(line + start, i - start);
	result = str_append(result, chunk);
	free(chunk);
	return (result);
}

static char	*expand_exit_status(char *result)
{
	char	*exit_status_str;
	char	*tmp;

	exit_status_str = ft_itoa(g_shell.exit_status);
	tmp = str_append(result, exit_status_str);
	free(exit_status_str);
	return (tmp);
}

static char	*change_hvalue(char *key, t_env *env)
{
	t_env	*en;
	char	*value;

	en = env;
	value = NULL;
	while (en)
	{
		if (ft_strcmp(key, en->key) == 0)
		{
			value = en->value;
			break ;
		}
		en = en->next;
	}
	return (value);
}

static char	*expand_variable(const char *line, int *i, t_env *env, char *result)
{
	int		keylen;
	char	*varname;
	char	*value;

	keylen = 0;
	value = NULL;
	while (ft_isalnum(line[*i + keylen]) || line[*i + keylen] == '_')
		keylen++;
	varname = get_word(line + *i, keylen);
	value = change_hvalue(varname, env);
	if (value)
		result = str_append(result, value);
	else
		result = str_append(result, "");
	free(varname);
	*i += keylen;
	return (result);
}

char	*helper_ex(const char *line, int *i, t_env *env, char *result)
{
	int	inc;

	inc = *i;
	if (line[inc] == '\0')
		return (str_append(result, "$"));
	if (line[inc] == '?')
		return (*i = ++inc, expand_exit_status(result));
	else if (ft_isalnum(line[inc]) || line[inc] == '_')
		return (expand_variable(line, i, env, result));
	else
		return (str_append(result, "$"));
}

char	*expand_line(const char *line, t_env *env)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$')
		{
			i++;
			result = helper_ex(line, &i, env, result);
		}
		else
		{
			result = nor_word(line, i, result);
			while (line[i] && line[i] != '$')
				i++;
		}
	}
	return (result);
}
