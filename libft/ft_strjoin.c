/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:42:02 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/07 07:17:24 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
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

/*
int main()
{
	const char *s1 = "Hello ";
	const char *s2 = "wol0d";
	char *joined = ft_strjoin(s1,s2);
	if(joined)
	{
		printf("The concatenated strings are %s\n",joined);
		free(joined);
	}
	else
		printf("Memory allocation failure.\n");
	return 0;
}*/
