/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:27:16 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/21 18:38:55 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}
/*
int	main(void) {
	char *str = NULL;

	printf("Original string: \"%s\"\n", str);

	// Using ft_bzero to set the first 5 characters to '\0'
	bzero(str + 5, 5);

	// Print the modified string
	printf("Modified string: \"%s\"\n", str);
	return (0);
}*/
