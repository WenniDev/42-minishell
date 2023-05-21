/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:53:18 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/21 16:30:16 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_command.h"
#include "minishell_expand.h"

void	skip_quotes(t_word_d *word)
{
	char	quote;
	int		i;

	i = 0;
	while (word->lval && word->lval[i])
	{
		while (word->lval[i] && word->lval[i] != '\'' && word->lval[i] != '"')
			i++;
		quote = word->lval[i];
		ft_memmove(&(word->lval[i]), &(word->lval[i + 1]),
			ft_strlen(&(word->lval[i])));
		while (word->lval[i] && word->lval[i] != quote)
			i++;
		ft_memmove(&(word->lval[i]), &(word->lval[i + 1]),
			ft_strlen(&(word->lval[i])));
	}
}

void	expand_word(t_word_d *word, t_word_lst **word_lst, int *status)
{
	if (word->flags & W_DOLLAR)
		expand_env(word, status);
	if (!(*status) && !(word->flags & W_NOEXPAND))
		expand_wildcard(word, word_lst, status);
	if (!(*status) && word->flags & W_QUOTES)
		skip_quotes(word);
}

void	check_cmd_name(t_word_lst **word_lst)
{
	t_word_lst	*begin;

	begin = *word_lst;
	if (!begin || ft_strcmp(begin->word->lval, "export"))
		return ;
	begin = begin->next;
	while (begin)
	{
		begin->word->flags |= W_NOEXPAND;
		begin = begin->next;
	}
}

int	expand(t_word_lst **word_lst)
{
	int			status;
	t_word_lst	*begin;

	status = 0;
	begin = (*word_lst);
	check_cmd_name(word_lst);
	while (begin && !status)
	{
		if (!status)
			expand_word(begin->word, word_lst, &status);
		begin = begin->next;
	}
	begin = (*word_lst);
	while (begin && !status)
		begin = begin->next;
	return (status);
}
