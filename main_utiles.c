/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 05:23:37 by mlakhdar          #+#    #+#             */
/*   Updated: 2025/07/18 05:25:40 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tabs_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
		i++;
	if (input[i] == '\0')
		return (0);
	else
		return (1);
}

void	init_commands(t_lst_cmd *cmds, t_env *envir)
{
	t_cmd	*cmd;

	cmd = cmds->head;
	while (cmd)
	{
		cmd->env = &envir;
		cmd->envp = env_tochar(envir);
		cmd = cmd->next;
	}
	cmd = cmds->head;
	if (!cmd->next && is_builtin(cmd->args[0]))
		g_shell.exit_status = execute_builtin(cmd, cmds);
	else
	{
		g_shell.child_running = 1;
		execute_pipeline(cmd, cmds);
		g_shell.child_running = 0;
	}
}

void	setup_shell_state(void)
{
	handle_signals();
	g_shell.child_running = 0;
}

void	exit_shell(void)
{
	write(1, "exit\n", 5);
	exit(g_shell.exit_status);
}
void	free_shell(t_lst_cmd *head)
{
	t_cmd		*tmp;
	t_env		*env;
	t_lst_hk	*x;

	tmp = head->head;
	env = *tmp->env;
	x = head->k;
	while (tmp)
	{
		free_array(tmp->envp);
		tmp = tmp->next;
	}
	free_all(x);
	free_env_list(env);
}
