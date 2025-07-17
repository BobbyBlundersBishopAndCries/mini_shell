/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:58:17 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/17 17:57:48 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	save_fds(t_redir *redir, int *saved_stdout, int *saved_stdin)
{
	if ((redir->index == R_OUT || redir->index == R_APPEND)
		&& *saved_stdout == -1)
		*saved_stdout = dup(STDOUT_FILENO);
	if ((redir->index == R_IN || redir->index == R_HEREDOC)
		&& *saved_stdin == -1)
		*saved_stdin = dup(STDIN_FILENO);
	return (0);
}

int	apply_redirections(t_redir *redir_list, int *saved_stdout, int *saved_stdin)
{
	t_redir	*current;

	current = redir_list;
	while (current)
	{
		current->fd = open_file(current, current->index);
		if (current->fd < 0)
			return (-1);
		save_fds(current, saved_stdout, saved_stdin);
		if (current->index == R_OUT || current->index == R_APPEND)
		{
			if (dup2(current->fd, STDOUT_FILENO) < 0)
				return (perror("dup2 output"), -1);
		}
		else if (current->index == R_IN || current->index == R_HEREDOC)
		{
			if (dup2(current->fd, STDIN_FILENO) < 0)
				return (perror("dup2 input"), -1);
		}
		current = current->next;
	}
	return (0);
}

void	restore_redirections(int saved_stdout, int saved_stdin)
{
	if (saved_stdout >= 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}

static void	refresh_envp_if_needed(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "export") == 0 || ft_strcmp(cmd->args[0],
			"unset") == 0)
	{
		if (cmd->envp)
			free_array(cmd->envp);
		cmd->envp = env_tochar(*(cmd->env));
	}
}

int	execute_builtin(t_cmd *cmd, t_lst_cmd *head)
{
	int	status;
	int	saved_stdout;
	int	saved_stdin;

	saved_stdin = -1;
	saved_stdout = -1;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (apply_redirections(cmd->files, &saved_stdout, &saved_stdin) < 0)
		return (1);
	if (!is_builtin(cmd->args[0]))
		return (1);
	status = handle_builtin_cmd(cmd, head);
	refresh_envp_if_needed(cmd);
	restore_redirections(saved_stdout, saved_stdin);
	return (status);
}
