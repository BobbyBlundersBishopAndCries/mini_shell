/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:38:45 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/20 13:38:47 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	heredoc_should_stop(char *line, char *delim)
{
	if (!line)
	{
		write(2, "\nminishell: warning: here-document delimited by EOF\n", 52);
		return (1);
	}
	if (ft_strncmp(line, delim, ft_strlen(delim)) == 0
		&& line[ft_strlen(delim)] == '\n')
		return (1);
	return (0);
}

static char	*process_heredoc_line(char *line, int quoted, t_env *env)
{
	char	*expanded;

	if (!quoted)
	{
		expanded = expand_line(line, env);
		free(line);
		return (expanded);
	}
	return (line);
}

static void	write_to_pipe_from_redir(t_redir *redir, int pipe_fd[2], t_env *env)
{
	char	*line;

	close(pipe_fd[0]);
	restore_signals_to_default();
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (heredoc_should_stop(line, redir->files))
		{
			free(line);
			break ;
		}
		line = process_heredoc_line(line, redir->deja_quoted, env);
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
}

void	heredoc_process(t_redir *redir, int pipe_fd[2], t_env *env)
{
	disable_echoctl();
	write_to_pipe_from_redir(redir, pipe_fd, env);
	exit(EXIT_SUCCESS);
}

int	heredoc_status(int status, t_redir *redir, int read_end)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		redir->fd = -1;
		g_shell.exit_status = 130;
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(read_end);
		redir->fd = -1;
		g_shell.exit_status = WEXITSTATUS(status);
		return (1);
	}
	return (0);
}
