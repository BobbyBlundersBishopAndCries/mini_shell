/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:40:50 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/31 13:55:30 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
/*
int main() {
    const char *str = NULL;
    char c = '\0';

    char *result = strchr(str, c);

    if (result) {
        printf("Found '%c' at position: %zu\n", c, result - str);
    } else {
        printf("Character '%c' not found.\n", c);
    }

    return 0;
}*/
