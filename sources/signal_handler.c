/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:53:59 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/16 12:54:00 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parse.h"

t_data	*g_msh;

void	handle_sigabrt(int signum)
{
	(void)signum;
	ft_putstr_fd(ABRTMSG, 2);
	ft_putchar_fd('\n', 2);
	reset_parser(&g_msh->parser);
	free(g_msh);
	exit(EXIT_FAILURE);
}

void	signal_handler(t_data *msh)
{
	g_msh = msh;
	signal(SIGABRT, handle_sigabrt);
//	signal(SIGINT, handle_sigint);
//	signal(SIGQUIT, handle_sigquit);
}
