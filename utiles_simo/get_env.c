/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:49:40 by feedback          #+#    #+#             */
/*   Updated: 2025/07/09 18:49:40 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dup_key(char *arg)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	j = 0;
	while (j < i)
	{
		key[j] = arg[j];
		j++;
	}
	key[i] = '\0';
	return (key);
}

char	*dup_value(char *arg)
{
	int		i;
	char	*value;
	int		len;
	int		j;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] != '=')
		return (NULL);
	i++;
	len = ft_strlen(arg + i);
	value = malloc(len + 1);
	if (!value)
		return (NULL);
	j = 0;
	while (j < len)
	{
		value[j] = arg[i + j];
		j++;
	}
	value[len] = '\0';
	return (value);
}

t_env	*create_env_node(char *arg)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = dup_key(arg);
	node->value = dup_value(arg);
	node->next = NULL;
	if (!node->key)
	{
		free(node->value);
		free(node);
		return (NULL);
	}
	return (node);
}

int	addback_node(t_env **head, char *av)
{
	t_env	*curr;
	t_env	*node;

	node = create_env_node(av);
	if (!node)
		return (1);
	curr = *head;
	if (*head == NULL)
	{
		*head = node;
		return (0);
	}
	while (curr->next)
		curr = curr->next;
	curr->next = node;
	return (0);
}

t_env	*get_env(char **env)
{
	int		i;
	t_env	*head;

	i = 0;
	head = NULL;
	while (env[i])
	{
		if (addback_node(&head, env[i]) == 1)
		{
			free_env_list(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}
