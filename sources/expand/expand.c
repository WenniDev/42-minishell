/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:53:18 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/15 16:30:31 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell_command.h"
# include "minishell_expand.h"
# include "libft.h"
# include "stdio.h"

#define debug_print(fmt, ...) \
        do { fprintf(stderr, "\e[1;34m%s\e[1;0m:\e[1;32m%d\e[1;0m:\e[1;0m\e[1;36m%s()\e[1;0m:	" fmt, __FILE_NAME__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

void	expand_word(t_word_d *word, t_word_lst *word_lst, int *status)
{
	if (word->flags & W_DOLLAR)
		expand_env(word, status);
	if (!(word->flags & W_NOEXPAND))
		expand_wildcard(&word_lst, status);
}

void expand_command_name(t_word_d *word, t_word_lst *word_lst, int *status)
{
	if (word->flags & W_DOLLAR)
		expand_env(word, status);
	if (!(word->flags & W_NOEXPAND))
		expand_wildcard(&word_lst, status);
	if (ft_strcmp(word_lst->word->lval, "export"))
		return ;
	word_lst = word_lst->next;
	while (word_lst)
	{
		word_lst->word->flags |= W_NOEXPAND;
		word_lst = word_lst->next;
	}
}

int expand(t_word_lst *word_lst)
{
	int 		status;
	t_word_lst	*begin;

	status = 0;
	expand_command_name(word_lst->word, word_lst, &status);
	if (status)
		return (status);
	begin = word_lst;
	word_lst = word_lst->next;
	while (word_lst && !status)
	{
		if (!status)
			expand_word(word_lst->word, word_lst, &status);
		word_lst = word_lst->next;
	}
	word_lst = begin;
	while (word_lst && !status)
	{
		debug_print("%s\n", word_lst->word->lval);
		word_lst = word_lst->next;
	}
	return (status);
}