/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:18:24 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/01 17:14:03 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_string(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	print_lst(t_lst_token *ltoken)
{
	t_token	*token;

	token = ltoken->head;
	while (token)
	{
		ft_printf(1, "token : [%s] type : [%d]\n", token->token, token->type);
		token = token->next;
	}
}

void	trim_space(char **input)
{
	int	size;

	if (!input || !(*input))
		return ;
	size = ft_strlen(*input);
	if (size == 0)
		return ;
	size--;
	while (size >= 0 && (*input)[size] == ' ')
	{
		(*input)[size] = '\0';
		size--;
	}
}

char	*ft_strdump(const char *s1, t_lst_hk *x)
{
	char	*result;
	size_t	i;

	i = ft_strlen(s1);
	result = ft_malloc(sizeof(char) * (i + 1), x);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
