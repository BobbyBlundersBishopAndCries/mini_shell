/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 02:51:34 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/06 07:53:30 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*abs_path;

	abs_path = getcwd(NULL, 0);
	if (!abs_path)
	{
		ft_printf(STDERR_FILENO, "pwd: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	ft_printf(STDOUT_FILENO, "%s\n", abs_path);
	free(abs_path);
	return (EXIT_SUCCESS);
}
