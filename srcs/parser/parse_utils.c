/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:54:19 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:54:20 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"

int	is_meta(char c)
{
	if (ft_strchr(META_CHARACTERS, c))
		return (1);
	return (0);
}

int	is_redir(int tk)
{
	if (tk == '<' || tk == LESS_LESS)
		return (INPUT_RED);
	if (tk == '>' || tk == GREATER_GREATER)
		return (OUTPUT_RED);
	return (0);
}

int	is_connector(int tk)
{
	if (tk == '|' || tk == AND_AND || tk == OR_OR)
		return (1);
	return (0);
}

/* read a char from the line and advance the line pointer */
char	get_char(char **ptr)
{
	return (*((*ptr)++));
}

/* move the line pointer backward */
void	unget_char(char **ptr)
{
	(*ptr)--;
}
