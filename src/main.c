/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktorvi <ktorvi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/02/17 13:09:12 by ktorvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigint2(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
	}
}
void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
}

int g_exit_codes[2];

int	main(int argc, char **argv, char **envp)
{
	char		**split_line;
	char		*line;
	t_envs		*envs;
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	envs = build_envs(envp);
	line = NULL;
	while (true)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		line = readline("$ ");
		signal(SIGINT, handle_sigint2);
		if (!line)
			kb_quit();
		else if (!ft_equalstr(line, ""))
		{
			split_line = ft_split(line, ' ');
			add_history(line);
			minishell = populate(split_line, envs);
			minishell->st_in = dup(STDIN_FILENO);
			execute_pipes(minishell, envs);
			dup2(minishell->st_in, STDIN_FILENO);
			free_tab(split_line);
		}
		if (line)
			reset_line(line);
	}
	return (0);
}
