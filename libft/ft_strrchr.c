/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:54:32 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/22 20:12:38 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	while (i > 0)
	{
		if (s[i - 1] == (char)c)
			return ((char *)&s[i - 1]);
		i--;
	}
	return (NULL);
}
// int main()
// {
// 	const char *s = NULL;
// 	char c = 'i';
// 	char *result = strrchr(s,c);
// 	if(result)
// 		printf("found %c at position : %zu\n",c,result - s);
// 	else
// 		printf("character not found\n");
// 	return 0;
// }