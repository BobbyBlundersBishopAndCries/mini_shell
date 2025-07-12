/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:02:03 by mohabid           #+#    #+#             */
/*   Updated: 2024/10/29 18:17:40 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] != '\0' && i + j < len)
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
/*
int main()
{
	const char *big = "this is the way by the way.";
	const char *little = "the way";
	char *result = ft_strnstr(big,little,sizeof(char) * ft_strlen(big));
	if(result)
		printf("%s\n",result);
	else
		printf("little doesn't exist in big in n length");
	return (0);
}*/
