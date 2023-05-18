/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:53:18 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/18 02:40:49 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell_command.h"
# include "minishell_expand.h"
# include "libft.h"
# include "stdio.h"
# include "signal.h"

#define debug_print(fmt, ...) \
        do { fprintf(stderr, "\e[1;34m%s\e[1;0m:\e[1;32m%d\e[1;0m:\e[1;0m\e[1;36m%s()\e[1;0m:	" fmt, __FILE__,\
                                __LINE__, __func__, __VA_ARGS__); } while (0)

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
		ft_memmove(&(word->lval[i]), &(word->lval[i + 1]), ft_strlen(&(word->lval[i])));
		while (word->lval[i] && word->lval[i] != quote)
			i++;
		ft_memmove(&(word->lval[i]), &(word->lval[i + 1]), ft_strlen(&(word->lval[i])));
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

void check_cmd_name(t_word_lst **word_lst)
{
	t_word_lst *begin;

	begin = *word_lst;
	if (ft_strcmp(begin->word->lval, "export"))
		return ;
	begin = begin->next;
	while (begin)
	{
		begin->word->flags |= W_NOEXPAND;
		begin = begin->next;
	}
}

int expand(t_word_lst **word_lst)
{
	int 		status;
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
	{
		debug_print("%s\n", begin->word->lval);
		begin = begin->next;
	}
	return (status);
}