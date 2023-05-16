/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:49:01 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/16 17:53:51 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_command.h"
#include "minishell_expand.h"
#include "signal.h"
#include "libft.h"

t_word_d 	*clone_word(t_word_d *src)
{
	t_word_d	*tmp_word;

	tmp_word = sfcalloc(1, sizeof(t_word_d));
	tmp_word->lval = ft_strdup(src->lval);
	if (!tmp_word->lval)
		return (free(tmp_word), kill(0, SIGABRT), (void *) NULL);
	tmp_word->flags = src->flags;
	return (tmp_word);
}

void	*expand_red(t_word_d *filename)
{
	int			status;
	t_word_lst	*tmp_lst;
	t_word_d	*tmp_word;

	status = 0;
	tmp_word = clone_word(filename);
	if (tmp_word->flags & W_DOLLAR)
		expand_env(tmp_word, &status);
	if (status)
		(free_word(tmp_word), kill(0, SIGABRT));
	tmp_lst = ft_calloc(1, sizeof(t_word_lst));
	if (!tmp_lst)
		(free_word(tmp_word), kill(0, SIGABRT));
	tmp_lst->word = tmp_word;
	expand_wildcard(&tmp_lst, &tmp_lst, &status);
	if (status)
		(free_word_lst(tmp_lst), kill(0, SIGABRT));
	if (ft_strchr(tmp_lst->word->lval, '*') || tmp_lst->next)
		return (free_word_lst(tmp_lst), NULL);
	free(filename->lval);
	filename->lval = ft_strdup(tmp_lst->word->lval);
	if (!filename->lval)
		(free_word_lst(tmp_lst), kill(0, SIGABRT));
	return (free_word_lst(tmp_lst), filename);
}