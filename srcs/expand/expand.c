/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:53:18 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/23 18:43:54 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_command.h"
#include "minishell_expand.h"

void	skip_quotes(char *word)
{
	char	quote;
	int		i;

	i = 0;
	while (word && word[i])
	{
		while (word[i] && word[i] != '\'' && word[i] != '"')
			i++;
		quote = word[i];
		ft_memmove(&(word[i]), &(word[i + 1]),
			ft_strlen(&(word[i])));
		while (word[i] && word[i] != quote)
			i++;
		ft_memmove(&(word[i]), &(word[i + 1]),
			ft_strlen(&(word[i])));
	}
}

void	expand_word(t_word_d *word, t_word_lst **word_lst, int *status)
{
	if (word->flags & W_DOLLAR)
		expand_env(word, status);
	if (!(*status) && !(word->flags & W_NOEXPAND))
		expand_wildcard(word, word_lst, status);
	if (!(*status) && word->flags & W_QUOTES)
		skip_quotes(word->lval);
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
