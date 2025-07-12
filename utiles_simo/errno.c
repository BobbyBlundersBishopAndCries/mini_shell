/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:49:32 by feedback          #+#    #+#             */
/*   Updated: 2025/07/09 18:49:52 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_error_status(int err)
{
	if (err == EACCES || err == EISDIR || err == ENOEXEC || err == ETXTBSY)
		return (126);
	if (err == ENOENT || err == ENOTDIR)
		return (127);
	return (1);
}
