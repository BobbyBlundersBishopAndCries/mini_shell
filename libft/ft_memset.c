/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:18:47 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/22 10:32:48 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
void	*ft_memset(void *s, int c, size_t n);

int main() {
    char *str = NULL;
    printf("Original string: %s\n", str);
    memset(str, 'X', 5);

    printf("Modified string: %s\n", str); // Output will be "XXXXX, World!"

    return 0;
}*/
