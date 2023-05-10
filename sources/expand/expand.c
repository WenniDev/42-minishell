/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:53:18 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/10 19:05:54 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell_command.h"
# include "libft.h"
# include "stdio.h"

#define debug_print(fmt, ...) \
        do { fprintf(stderr, "\e[1;34m%s\e[1;0m:\e[1;32m%d\e[1;0m:\e[1;0m\e[1;36m%s()\e[1;0m:	" fmt, __FILE_NAME__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

void	expand_wildcard(t_word_d *word, int *status)
{
	(void)word;
	debug_print("%s with *\n", word->lval, NULL);
	*status = 0;
}

void	expand_env(t_word_d *word, int *status)
{
	(void)word;
	debug_print("%s with $\n", word->lval, NULL);
	*status = 0;
}

void	expand_word(t_word_d *word, int *status)
{
	if (word->flags & W_DOLLAR)
		expand_env(word, status);
	if (!(word->flags & W_NOEXPAND))
		expand_wildcard(word, status);
}

void expand_command_name(t_word_d *word, t_word_lst *sentence, int *status)
{
	if (word->flags & W_DOLLAR)
		expand_env(word, status);
	if (!(word->flags & W_NOEXPAND))
		expand_wildcard(word, status);
	if (ft_strcmp(word->lval, "export"))
		return ;
	sentence = sentence->next;
	while (sentence)
	{
		sentence->word->flags |= W_NOEXPAND;
		sentence = sentence->next;
	}
}

int expand(t_command_lst *commands)
{
	t_word_lst	*word_lst;
	int 		status;

	status = 0;
	word_lst = commands->cmd.elem.words;
	expand_command_name(word_lst->word, word_lst, &status);
	if (status)
		return (status);
	word_lst = word_lst->next;
	while (word_lst && !status)
	{
		if (!status)
			expand_word(word_lst->word, &status);
		word_lst = word_lst->next;
	}
	return (status);
}