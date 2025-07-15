/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:29:43 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/15 17:33:32 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*str_append(char *dst, const char *src)
{
	size_t	len_dst;
	size_t	len_src;
	char	*res;

	if (!src)
		return (dst);
	if (!dst)
		return (strdup(src));
	len_dst = strlen(dst);
	len_src = strlen(src);
	res = malloc(len_dst + len_src + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, dst, len_dst);
	ft_memcpy(res + len_dst, src, len_src);
	res[len_dst + len_src] = '\0';
	free(dst);
	return (res);
}

static char	*get_word(const char *word, int size)
{
	char	*w;

	w = malloc(size + 1);
	if (!w)
		return (NULL);
	memcpy(w, word, size);
	w[size] = '\0';
	return (w);
}
static char *nor_word(const char *line , int i, char *result )
{
  int start;
  start = i;
  char *chunk;

  chunk = NULL;
  while (line[i] && line[i] != '$')
    i++;
  chunk = get_word(line + start, i - start);
  result = str_append(result, chunk);
  free(chunk);
  return result;
}

char	*expand_line(const char *line, t_env *env)
{
	char	*result;
	int		i;
	char	*exit_status_str;
	int		keylen;
	char	*varname;
	char	*value;

	result = NULL;
	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '\0')
			{
				result = str_append(result, "$");
				break ;
			}
			if (line[i] == '?')
			{
				exit_status_str = ft_itoa(g_shell.exit_status);
				result = str_append(result, exit_status_str);
				free(exit_status_str);
				i++;
			}
			else if (ft_isalnum(line[i]) || line[i] == '_')
			{
				keylen = 0;
				while (ft_isalnum(line[i + keylen]) || line[i + keylen] == '_')
					keylen++;
				varname = get_word(line + i, keylen);
				value = NULL;
				for (t_env *etmp = env; etmp; etmp = etmp->next)
				{
					if (ft_strcmp(varname, etmp->key) == 0)
					{
						value = etmp->value;
						break ;
					}
				}
				result = str_append(result, value ? value : "");
				free(varname);
				i += keylen;
			}
			else
				result = str_append(result, "$");
		}
		else
      result = nor_word(line, i, result);
  }
	return (result);
}


static void	write_to_pipe_from_redir(t_redir *redir, int pipe_fd[2], t_env *env)
{
	char	*line;
	int		count;
	char	*expanded;

	count = 1;
	close(pipe_fd[0]);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			write(2, "\nminishell: warning: here-document delimited by EOF\n",
				52);
			break ;
		}
		if (ft_strncmp(line, redir->files, ft_strlen(redir->files)) == 0
			&& line[ft_strlen(redir->files)] == '\n')
		{
			free(line);
			break ;
		}
		if (line && !redir->deja_quoted)
		{
			expanded = expand_line(line, env);
			free(line);
			line = expanded;
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
	int		sig;

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
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT || sig == SIGQUIT)
		{
			redir->fd = -1;
			g_shell.exit_status = 128 + sig;
			return (1);
		}
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
