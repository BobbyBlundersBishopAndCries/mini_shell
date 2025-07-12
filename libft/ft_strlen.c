/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:53:39 by mohabid           #+#    #+#             */
/*   Updated: 2024/11/01 13:55:31 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*int main() 
{
    char *str= NULL;
    size_t length = ft_strlen(str);
    printf("The length of the string \"%s\" is %zu.\n", str, length);

    return 0;
}*/
