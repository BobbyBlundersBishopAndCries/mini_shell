/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 06:31:59 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/07 07:25:44 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_from_fd(int fd)
{
	char	*temp;
	int		bytes_read;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(temp);
		return (NULL);
	}
	temp[bytes_read] = '\0';
	return (temp);
}

static char	*update_buffer(char **buffer, char *temp)
{
	char	*new_buffer;

	new_buffer = ft_strjointwo(*buffer, temp);
	free(*buffer);
	*buffer = new_buffer;
	return (*buffer);
}

static char	*read_to_buffer(int fd, char **buffer)
{
	char	*temp;

	while (!ft_strchrtwo(*buffer, '\n'))
	{
		temp = read_from_fd(fd);
		if (!temp)
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		if (*temp == '\0')
		{
			free(temp);
			break ;
		}
		update_buffer(buffer, temp);
		free(temp);
	}
	return (*buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	buffer = read_to_buffer(fd, &buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = new_line(buffer);
	return (line);
}