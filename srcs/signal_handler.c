/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:01:11 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 11:01:12 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parse.h"

t_data	*g_msh;

void	redisplay(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
	}
	if (signum == SIGQUIT)
		printf("\r\e[K");
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigabrt(int signum)
{
	(void)signum;
	clean_all(g_msh);
	exit(EXS_SIGSEG);
}

void	handle_sigint(int signum)
{
	g_msh->exec.status = 130;
	if (g_msh->parser.state & PST_HEREDOC)
	{
		printf("\n");
		close(STDIN_FILENO);
		g_msh->parser.state &= ~PST_HEREDOC;
	}
	else if (!g_msh->exec.child_nb)
		redisplay(signum);
	else
		printf("\b\b");
}

void	handle_sigquit(int signum)
{
	if (!g_msh->exec.child_nb)
		redisplay(signum);
	else
		printf("\b\b");
}

void	signal_handler(t_data *msh)
{
	g_msh = msh;
	signal(SIGABRT, handle_sigabrt);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
