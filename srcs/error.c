/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:00:16 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 11:00:17 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_error.h"
#include "minishell_parse.h"

const char	*tk_translate(int tk);

int	malloc_error(void)
{
	ft_putstr_fd(EMFAILED, 2);
	ft_putchar_fd('\n', 2);
	kill(0, SIGABRT);
	return (EXIT_FAILURE);
}

int	quote_error(char quote)
{
	ft_putstr_fd("msh error: ", 2);
	ft_putstr_fd(EUNEOL, 2);
	ft_putchar_fd(quote, 2);
	ft_putchar_fd('\'', 2);
	ft_putchar_fd('\n', 2);
	return (TOKEN_ERROR);
}

int	syntax_error(char *error, int tk, char *lvl)
{
	ft_putstr_fd("msh: syntax error: ", 2);
	if (tk == '\'' || tk == '"')
		return (quote_error((char)tk));
	ft_putstr_fd(error, 2);
	if (tk)
	{
		if (tk == WORD)
			ft_putstr_fd(lvl, 2);
		else
			ft_putstr_fd((char *)tk_translate(tk), 2);
	}
	ft_putchar_fd('\n', 2);
	return (EXS_ERROR);
}

int	msh_error(char *error)
{
	ft_putstr_fd("msh: ", 2);
	if (errno)
		perror(error);
	else
	{
		ft_putstr_fd(error, 2);
		ft_putchar_fd('\n', 2);
	}
	kill(0, SIGABRT);
	return (EXIT_FAILURE);
}

int	print_error(char *error, char *infos, char *infos2)
{
	ft_putstr_fd("msh: ", 2);
	ft_putstr_fd(infos, 2);
	ft_putstr_fd(": ", 2);
	if (infos2)
	{
		ft_putstr_fd(infos2, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error, 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}
