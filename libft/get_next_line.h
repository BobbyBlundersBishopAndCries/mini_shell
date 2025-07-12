/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:00:46 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/07 07:26:30 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include "libft.h"

size_t	ft_strlentwo(char *s);
char	*ft_strchrtwo(char *s, int c);
char	*ft_strjointwo(char *s1, char *s2);
char	*get_next_line(int fd);
char	*extract_line(char *buffer);
char	*new_line(char *buffer);
#endif