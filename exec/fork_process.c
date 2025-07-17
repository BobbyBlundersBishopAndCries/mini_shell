/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:52:31 by feedback          #+#    #+#             */
/*   Updated: 2025/07/17 14:47:04 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_or_builtin(t_cmd *cmd, t_lst_cmd *head)
{
	if (is_builtin(cmd->args[0]))
	{
		g_shell.exit_status = execute_builtin(cmd, head);
		{
			free_shellax(head);
			exit(g_shell.exit_status);
		}
	}
	execute_command(cmd, head);
	exit(EXIT_FAILURE);
}

static void	setup_child_fds(t_cmd *cmd, int prev_fd[2], int next_fd[2])
{
	if (prev_fd[0] != -1)
	{
		dup2(prev_fd[0], STDIN_FILENO);
		close(prev_fd[0]);
	}
	if (cmd->next)
	{
		close(next_fd[0]);
		dup2(next_fd[1], STDOUT_FILENO);
		close(next_fd[1]);
	}
}

static void	child_process_execution(t_cmd *cmd, int prev_fd[2], int next_fd[2],
		t_lst_cmd *head)
{
	restore_signals_to_default();
	setup_child_fds(cmd, prev_fd, next_fd);
	if (setup_redirections(cmd->files))
	{
		free_shellax(head);
		exit(EXIT_FAILURE);
	}
	close_redirs(cmd->files);
	exec_or_builtin(cmd, head);
}

static pid_t	pipe_and_fork(t_cmd *cmd, int next_fd[2], int prev_fd[2],
		t_lst_cmd *head)
{
	pid_t	pid;

	next_fd[0] = -1;
	next_fd[1] = -1;
	if (cmd->next && pipe(next_fd) == -1)
		error();
	g_shell.child_running = 1;
	pid = fork();
	if (pid < 0)
		error();
	if (pid == 0)
		child_process_execution(cmd, prev_fd, next_fd, head);
	return (pid);
}

void	fork_and_execute(t_cmd *cmd, int prev_fd[2], t_lst_cmd *head,
		t_fork_info *info)
{
	int		next_fd[2];
	pid_t	pid;

	pid = pipe_and_fork(cmd, next_fd, prev_fd, head);
	info->pids[(*info->count)++] = pid;
	if (prev_fd[0] != -1)
		close(prev_fd[0]);
	if (cmd->next)
	{
		prev_fd[0] = next_fd[0];
		close(next_fd[1]);
	}
	else
		prev_fd[0] = -1;
}
