/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:58:35 by feedback          #+#    #+#             */
/*   Updated: 2025/07/12 10:24:57 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_state	g_shell = {.exit_status = 0, .sigint_received = 0,
		.in_heredoc = 0, .child_running = 0};
		
int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_lst_cmd	*cmds;
	t_cmd		*cmd;
	t_env		*envir;

	(void)argc;
	(void)argv;
	envir = get_env(envp);
	while (1)
	{
		handle_signals();
		g_shell.child_running = 0;
		input = readline("minishell:$ ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*input)
			add_history(input);
		cmds = parsing(input, envir, &g_shell.exit_status);
		free(input);
		if (!cmds || !cmds->head)
			continue ;
		cmd = cmds->head;
		while (cmd)
		{
			cmd->env = &envir;
			cmd->envp = env_tochar(envir);
			cmd = cmd->next;
		}
		cmd = cmds->head;
		if (!cmd->next && is_builtin(cmd->args[0]))
			g_shell.exit_status = execute_builtin(cmd);
		else
		{
			g_shell.child_running = 1;
			execute_pipeline(cmd);
			g_shell.child_running = 0;
		}
		free_all(cmds->k);
	}
	return (g_shell.exit_status);
}
