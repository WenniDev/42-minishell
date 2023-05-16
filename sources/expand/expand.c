/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:53:18 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/16 19:42:30 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell_command.h"
# include "minishell_expand.h"
# include "libft.h"
# include "stdio.h"
# include "signal.h"

#define debug_print(fmt, ...) \
        do { fprintf(stderr, "\e[1;34m%s\e[1;0m:\e[1;32m%d\e[1;0m:\e[1;0m\e[1;36m%s()\e[1;0m:	" fmt, __FILE_NAME__,\
                                __LINE__, __func__, __VA_ARGS__); } while (0)

void	expand_word(t_word_d *word, t_word_lst **word_lst,
			t_word_lst **begin, int *status)
{
	if (word->flags & W_DOLLAR)
		expand_env(word, status);
	if (!(word->flags & W_NOEXPAND))
		expand_wildcard(word_lst, begin, status);
}

void expand_command_name(t_word_d *word, t_word_lst **word_lst, int *status)
{
	t_word_lst *begin;

	begin = *word_lst;
	if (word->flags & W_DOLLAR)
		expand_env(word, status);
	if (!(word->flags & W_NOEXPAND))
		expand_wildcard(word_lst, &begin, status);
	if (ft_strcmp((*word_lst)->word->lval, "export"))
		return ;
	begin = *word_lst;
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
	t_word_lst	*lst;

	status = 0;
	lst = (*word_lst);
	expand_command_name((*word_lst)->word, word_lst, &status);
	if (status)
		return (status);
	lst = lst->next;
	while (lst && !status)
	{
		if (!status)
			expand_word(lst->word, &lst, word_lst, &status);
		lst = lst->next;
	}
	lst = (*word_lst);
	while (lst && !status)
	{
		debug_print("%s\n", lst->word->lval);
		lst = lst->next;
	}
	kill(0, SIGABRT);
	return (status);
}