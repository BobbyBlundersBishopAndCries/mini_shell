/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:39:58 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/06 18:28:27 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
int main() {
	//strdup(NULL);
 	const char *original = NULL;
    char *copy = ft_strdup(original);

    if (copy) {
        printf("Original: %s\n", original);
        printf("Copy: %s\n", copy);
        free(copy);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}*/
