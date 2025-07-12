/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:50:09 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/07 07:25:27 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlentwo(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
	{
		len++;
	}
	return (len);
}

char	*ft_strchrtwo(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)(s + ft_strlen(s)));
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_strjointwo(char *s1, char *s2)
{
	size_t	len;
	char	*joined;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = (char *)malloc(len * sizeof(char));
	if (!joined)
		return (NULL);
	while (s1[i])
	{
		joined[i] = ((char *)s1)[i];
		i++;
	}
	while (s2[j])
		joined[i++] = ((char *)s2)[j++];
	joined[i] = '\0';
	return (joined);
}

char	*extract_line(char *line)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	if (!line[i] || !line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = line[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*new_line(char *buffer)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	str = (char *)malloc(sizeof(char) * (ft_strlentwo(buffer) - i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (buffer[i] != '\0')
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(buffer);
	return (str);
}