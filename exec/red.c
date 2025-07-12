/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:52:36 by feedback          #+#    #+#             */
/*   Updated: 2025/07/09 18:52:36 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(t_redir *redir, t_redirct mode)
{
	int	fd;

	fd = -1;
	if (!redir || !redir->files)
		return (-1);
	if (mode == R_OUT)
		fd = open(redir->files, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == R_APPEND)
		fd = open(redir->files, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == R_IN)
		fd = open(redir->files, O_RDONLY);
	else if (mode == R_HEREDOC)
		fd = redir->fd;
	if (fd < 0)
		perror("open_file");
	return (fd);
}

int	redirect_fd(int fd, int std_fd)
{
	if (dup2(fd, std_fd) == -1)
	{
		perror("dup2 error");
		return (1);
	}
	return (0);
}

int	apply_single_redirection(t_redir *redir)
{
	int	std_fd;

	if (!redir)
		return (1);
	if (redir->index == R_OUT || redir->index == R_APPEND)
		std_fd = STDOUT_FILENO;
	else if (redir->index == R_IN || redir->index == R_HEREDOC)
		std_fd = STDIN_FILENO;
	else
		return (1);
	redir->fd = open_file(redir, redir->index);
	if (redir->fd < 0)
		return (1);
	if (redirect_fd(redir->fd, std_fd))
		return (1);
	return (0);
}

int	setup_redirections(t_redir *list)
{
	while (list)
	{
		if (apply_single_redirection(list))
			return (1);
		list = list->next;
	}
	return (0);
}

void	close_redirs(t_redir *list)
{
	t_redir	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->fd > 2)
			close(tmp->fd);
		tmp = tmp->next;
	}
}
