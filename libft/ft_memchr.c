/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:30:59 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/31 13:58:26 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*d;

	i = 0;
	d = (const unsigned char *)s;
	while (i < n)
	{
		if (d[i] == (unsigned char)c)
			return ((void *)(d + i));
		i++;
	}
	return (NULL);
}

/*int main() {
    const char *str = NULL;
    char c = '\0';

    void *result = ft_memchr(str, '\t', 0);

    if (result) {
        printf("Found '%c' at position: %zu\n", c,\
       	(unsigned char *)result - (unsigned char *)str);
    } else {
        printf("Character '%c' not found.\n", c);
    }

    return 0;
}*/
