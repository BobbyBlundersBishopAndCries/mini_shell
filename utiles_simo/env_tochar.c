/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tochar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:49:29 by feedback          #+#    #+#             */
/*   Updated: 2025/07/09 18:49:29 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_nodes(t_env *lst)
{
	int		count;
	t_env	*curr;

	count = 0;
	curr = lst;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*strjoin_val_path(char *s1, char *s2, int flag)
{
	char	*temp;
	char	*full;

	if (flag == 1)
	{
		if (s1[ft_strlen(s1) - 1] == '/')
			temp = ft_strdup(s1);
		else
			temp = ft_strjoin(s1, "/");
	}
	else if (flag == 2)
		temp = ft_strjoin(s1, "=");
	else
		temp = ft_strdup(s1);
	if (!temp)
		return (NULL);
	full = ft_strjoin(temp, s2);
	free(temp);
	return (full);
}

char	**env_tochar(t_env *env)
{
	int		i;
	char	**ev;
	t_env	*curr;

	i = count_nodes(env);
	ev = (char **)malloc((i + 1) * sizeof(char *));
	if (!ev)
		return (NULL);
	curr = env;
	i = 0;
	while (curr)
	{
		ev[i] = strjoin_val_path(curr->key, curr->value, 2);
		if (!ev[i])
			free_array(ev);
		i++;
		curr = curr->next;
	}
	ev[i] = NULL;
	return (ev);
}
