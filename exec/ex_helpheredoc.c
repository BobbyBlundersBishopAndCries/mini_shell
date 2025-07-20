/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_helpheredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:35:39 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/20 13:35:43 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_word(const char *word, int size)
{
	char	*w;

	w = malloc(size + 1);
	if (!w)
		return (NULL);
	memcpy(w, word, size);
	w[size] = '\0';
	return (w);
}

char	*str_append(char *dst, const char *src)
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

char	*expand_exit_status(char *result)
{
	char	*exit_status_str;
	char	*tmp;

	exit_status_str = ft_itoa(g_shell.exit_status);
	tmp = str_append(result, exit_status_str);
	free(exit_status_str);
	return (tmp);
}
