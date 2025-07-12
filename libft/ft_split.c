/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 02:21:35 by mohabid           #+#    #+#             */
/*   Updated: 2024/11/06 17:32:47 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static void	ft_free(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**ft_helper(char const *s, char **lst, char c)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			lst[i++] = ft_substr(s, 0, word_len);
			if (lst[i - 1] == 0)
			{
				ft_free(lst);
				return (NULL);
			}
			s += word_len;
		}
	}
	lst[i] = NULL;
	return (lst);
}

char	**ft_split(char const *s, char c)
{
	char	**lst;

	if (!s)
		return (NULL);
	lst = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!lst)
		return (NULL);
	lst = ft_helper(s, lst, c);
	return (lst);
}

/*int	main(void)
{
	const char	*cla;
	size_t		i;

	cla = NULL;
	char **tab = ft_split(cla, 'z');
	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			printf("tab[%zu] = %s\n", i, tab[i]);
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	return (0);
}*/
