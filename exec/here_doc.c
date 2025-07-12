/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:29:43 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/12 13:06:21 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_word(char *word, int size)
{
	char	*w;
	int		i;

	w = malloc(sizeof(char) * (size + 1));
	if (!w)
		return (NULL);
	i = 0;
	while (i < size)
	{
		w[i] = word[i];
		i++;
	}
	w[i] = '\0';
	return (w);
}

char	*expand_line(char *line, t_env *env)
{
	char	*value;
	char	*line_ex;
	char	*t;
	t_env	*etmp;
	int		i;

	line_ex = NULL;
	value = NULL;
	t = NULL;
	etmp = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			int	key = 0;

			while (ft_isalnum(line[i + key]))
				key++;
			if (key > 0)
			{
				t = get_word(line + i, key);
				etmp = env;
				while (etmp)
				{
					if (ft_strcmp(t, etmp->key) == 0)
					{
						value = etmp->value;
						break ;
					}
					etmp = etmp->next;
				}
				if (!etmp && value == NULL)
					value = ft_strdup("");
				line_ex = ft_strjoin(line_ex, value);
				i += key;
				free(t);
			}
			else
			{
				/* Handle special cases like $? or $ followed by non-alnum */
				if (line[i] == '?')
				{
					value = ft_itoa(g_shell.exit_status);
					line_ex = ft_strjoin(line_ex, value);
					free(value);
					i++;
				}
				else
					line_ex = ft_strjoin(line_ex, "$");
			}
		}
		else
		{
			int		w_len = 0;
			char	*word;

			while (line[i + w_len] && line[i + w_len] != '$')
				w_len++;
			word = get_word(line + i, w_len);
			line_ex = ft_strjoin(line_ex, word);
			free(word);
			i += w_len;
		}
	}
	if (line_ex && line_ex[0] != '\0')
	{
		char *tmp = ft_strjoin(line_ex, "\n");
		free(line_ex);
		line_ex = tmp;
	}
	return (line_ex);
}

static void	write_to_pipe_from_redir(t_redir *redir, int pipe_fd[2], t_env *env)
{
	char	*line;
	int		count;

	count = 1;
	close(pipe_fd[0]);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line && !redir->deja_quoted)
		{
			char *expanded = expand_line(line, env);
			free(line);
			line = expanded;
		}
		if (!line)
		{
			ft_printf(2, "minishell: warning: here-document delimited at line %d "
				"by end-of-file (wanted `%s')\n", count, redir->files);
			break ;
		}
		if (ft_strncmp(line, redir->files, ft_strlen(redir->files)) == 0
			&& line[ft_strlen(redir->files)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		count++;
	}
	close(pipe_fd[1]);
}

int	handle_heredoc(t_redir *redir, t_env *env)
{
	pid_t	id;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd) == -1)
		return (1);
	g_shell.in_heredoc = 1;
	id = fork();
	if (id < 0)
		return (1);
	if (id == 0)
	{
		restore_signals_to_default();
		write_to_pipe_from_redir(redir, pipe_fd, env);
		exit(EXIT_SUCCESS);
	}
	close(pipe_fd[1]);
	waitpid(id, &status, 0);
	g_shell.in_heredoc = 0;
	handle_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		redir->fd = -1;
		g_shell.exit_status = 130;
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipe_fd[0]);
		redir->fd = -1;
		g_shell.exit_status = WEXITSTATUS(status);
		return (1);
	}
	redir->fd = pipe_fd[0];
	return (0);
}

int	handle_all_heredocs(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*redir;

	tmp = cmd;
	while (tmp)
	{
		redir = tmp->files;
		while (redir)
		{
			if (redir->index == R_HEREDOC)
			{
				if (handle_heredoc(redir, *(tmp->env)) != 0)
					return (1);
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
