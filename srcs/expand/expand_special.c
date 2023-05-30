/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:46:58 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/30 22:35:26 by jopadova         ###   ########.fr       */
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
	char	*str;

	str = word->lval;
	while (str && *str && (*str == '\'' || *str == '"'))
		str++;
	if (!ft_strcmp(str, "$"))
		return (1);
	if (str[0] == '$' && (str[1] == '\'' || str[1] == '"'))
		return (0);
	if (str[0] != '$')
		return (0);
	if (str[1] == '?')
		return (0);
	if (word->flags & W_QUOTES && (str[1] == '\'' || str[1] == '"'))
		return (1);
	if (!(ft_isalnum(str[1]) || str[1] == '_'))
		return (1);
	return (0);
}
