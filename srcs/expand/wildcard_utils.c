/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:34:32 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/21 16:32:46 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_command.h"
#include <dirent.h>
#include <sys/stat.h>
#include "libft.h"

t_word_lst	*get_next_word(t_word_d *word, t_word_lst **word_lst)
{
	t_word_lst	*begin_lst;

	begin_lst = (*word_lst);
	while (begin_lst->next && word != begin_lst->word)
		begin_lst = begin_lst->next;
	return (begin_lst->next);
}

t_word_lst	*get_word_in_list(t_word_d *word, t_word_lst **word_lst)
{
	t_word_lst	*begin_lst;

	begin_lst = (*word_lst);
	while (begin_lst && word != begin_lst->word)
		begin_lst = begin_lst->next;
	return (begin_lst);
}

void	insert_list(t_word_d *word, t_word_lst **word_lst, t_word_lst **tmp_lst)
{
	t_word_lst	*begin_tmp;
	t_word_lst	*curr_word;

	if (!(*tmp_lst))
		return ;
	begin_tmp = *tmp_lst;
	while (begin_tmp->next)
		begin_tmp = begin_tmp->next;
	begin_tmp->next = get_next_word(word, (word_lst));
	curr_word = get_word_in_list(word, word_lst);
	free(curr_word->word->lval);
	curr_word->word->lval = (*tmp_lst)->word->lval;
	curr_word->word->flags = (*tmp_lst)->word->flags;
	curr_word->next = (*tmp_lst)->next;
	free((*tmp_lst)->word);
	free((*tmp_lst));
}

int	is_dir_pattern(char *pattern)
{
	if (*pattern && pattern[ft_strlen(pattern) - 1] == '/')
		return (1);
	else
		return (0);
}

int	is_dir(struct dirent *ent)
{
	struct stat	info;

	if (stat(ent->d_name, &info) != 0)
		return (0);
	if (S_ISDIR(info.st_mode))
		return (1);
	return (0);
}
