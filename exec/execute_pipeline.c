/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:02:14 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/16 23:45:22 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_pipeline(pid_t *pids, int count)
{
	int		status;
	int		exit_status;
	int		i;
	
	i = 0;
	exit_status = 0;
	while (i < count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			continue;
		}
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	g_shell.exit_status = exit_status;
}

static bool validate_pipeline(t_cmd *cmd)
{
	t_redir *r;
	
	if (handle_all_heredocs(cmd))
		return false;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		if (cmd != NULL)
			r = cmd->files;
		else
			r = NULL;
		while (r)
		{
			if (r->index == R_HEREDOC && r->fd > 2)
				close(r->fd);
			r = r->next;
		}
		g_shell.exit_status = 0;
		return false;
	}
	return true;
}

void execute_pipeline(t_cmd *cmd, t_lst_cmd *head)
{
	int prev_fd[2] = {-1, -1};
	t_cmd	*tmp;
	pid_t pids[PID_MAX];
	int count;
	
	tmp = cmd;
	count = 0;
	t_fork_info info = {pids, &count};

	if (!validate_pipeline(cmd))
		return;

	while (tmp)
	{
		fork_and_execute(tmp, prev_fd, head, &info);
		tmp = tmp->next;
	}
	handle_signals();
	wait_for_pipeline(info.pids, count);
	g_shell.child_running = 0;
}
