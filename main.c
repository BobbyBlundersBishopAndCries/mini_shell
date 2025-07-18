/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:58:35 by feedback          #+#    #+#             */
/*   Updated: 2025/07/18 05:27:35 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_state	g_shell = {.exit_status = 0, .in_heredoc = 0,
		.child_running = 0};

void	shell_loop(t_env *envir)
{
	char		*input;
	t_lst_cmd	*cmds;
	t_cmd *tmp;

	while (1)
	{
		setup_shell_state();
		input = readline("minishell:$ ");
		if (!input)
		{
			free_env_list(envir);
			exit_shell();
		}
		if (!check_tabs_spaces(input))
		{
			free(input);
			continue ;
		}
		if (*input)
			add_history(input);
		cmds = parsing(input, envir, &g_shell.exit_status);
		free(input);
		if (!cmds || !cmds->head)
		{
			if (cmds)
				free_all(cmds->k);
			continue ;
		}
		init_commands(cmds, envir);
		close_redirs(cmds->head->files);
		tmp = cmds->head;
		while (tmp)
		{
			free_array(tmp->envp);
			tmp = tmp->next;
		}
		free_all(cmds->k);
	}
	free_env_list(envir);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envir;

	(void)argc;
	(void)argv;
	envir = get_env(envp);
	shell_loop(envir);
	return (g_shell.exit_status);
}
