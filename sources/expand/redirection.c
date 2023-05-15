/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:49:01 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/15 18:33:08 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_command.h"
#include "minishell_expand.h"
#include "signal.h"
#include "libft.h"

void	clone_word(t_word_d *dest, t_word_d *src)
{
	dest = sfcalloc(1, sizeof(t_word_d));
	dest->lval = ft_strdup(src->lval);
	dest->flags = src->flags;
}

t_red	*expand_red(t_red *r)
{
	int			status;
	t_word_lst	*tmp_lst;
	t_word_d	*tmp_word;

	clone_word(tmp_word, r->filename);
	if (tmp_word->flags & W_DOLLAR)
		expand_env(tmp_word, &status);
	if (status)
		(free_word_lst(tmp_lst), kill(0, SIGABRT));
	tmp_lst = ft_calloc(1, sizeof(t_word_lst));
	if (!tmp_lst)
		(free_word(tmp_word), kill(0, SIGABRT));
	tmp_lst->word = tmp_word;
	expand_wildcard(&tmp_lst, &status);
	if (status)
		(free_word_lst(tmp_lst), kill(0, SIGABRT));
	if (ft_strchr(tmp_lst->word->lval, '*') || tmp_lst->next)
		return (free_word_lst(tmp_lst), NULL);
	return (free_word_lst(tmp_lst), r);
}