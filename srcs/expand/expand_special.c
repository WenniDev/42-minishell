/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:46:58 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:47:21 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_command.h"
#include "minishell_expand.h"
#include "minishell_utils.h"
#include "libft.h"
#include "signal.h"
#include "stdio.h"

int	expand_special(t_word_d *word)
{
	if (!ft_strcmp(word->lval, "$"))
		return (1);
	if (word->lval[0] != '$')
		return (0);
	if (word->lval[1] == '?')
		return (0);
	if (!(ft_isalnum(word->lval[1]) || word->lval[1] == '_'))
		return (1);
	return (0);
}
