/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:25:42 by feedback          #+#    #+#             */
/*   Updated: 2025/07/09 18:26:34 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_par(char *name, t_env *env)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (ft_strcmp(head->key, name) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

char	*change_value(char *key, size_t count, t_lst_hk *x, t_env *env)
{
	char	*name;
	char	*val;

	name = ft_malloc(count + 1, x);
	strncpy(name, key, count);
	name[count] = '\0';
	val = get_env_par(name, env);
	if (val)
		return (val);
	return (ft_strdump("", x));
}

char	*ft_join(const char *s1, const char *s2, t_lst_hk *x)
{
	size_t	i;
	size_t	k;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	joined = ft_malloc(sizeof(char) * (i + 1), x);
	if (!joined)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		joined[k + i] = s2[k];
		k++;
	}
	joined[k + i] = '\0';
	return (joined);
}
