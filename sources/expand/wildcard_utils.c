/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:34:32 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/16 19:43:25 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_command.h"
#include <dirent.h>
#include <sys/stat.h>
#include "libft.h"

//void	insert_list(t_word_lst **word_lst, t_word_lst **begin, t_word_lst *tmp)
//{
//	t_word_lst	*next_word;
//	t_word_lst	*begin_tmp;
//	t_word_lst	*begin_word;
//	t_word_lst	*to_free;
//
//	if (!tmp)
//		return ;
//	next_word = (*word_lst)->next;
//	begin_tmp = tmp;
//	while (begin_tmp->next)
//		begin_tmp = begin_tmp->next;
//	begin_tmp->next = next_word;
//	begin_word = (*begin);
//	if (!ft_strcmp((*word_lst)->word->lval, (*begin)->word->lval))
//	{
//		free(begin_word->word->lval); begin_word->word->lval = NULL;
//		free(begin_word->word); begin_word->word = NULL;
//		free(begin_word); begin_word = NULL;
//		(*begin) = (*word_lst);
//	}
//	else
//	{
//		while (begin_word->next && ft_strcmp((*word_lst)->word->lval, begin_word->next->word->lval))
//			begin_word = begin_word->next;
//		to_free = begin_word->next;
//		free(to_free->word->lval);
//		free(to_free->word);
//		free(to_free);
//		begin_word->next = tmp;
////		(*word_lst) = tmp;
//	}
//}

void	free_word(t_word_d *word)
{
	free(word->lval);
	free(word);
}

void	free_word_lst(t_word_lst *word_lst)
{
	t_word_lst	*tmp;

	while (word_lst)
	{
		tmp = word_lst->next;
		free_word(word_lst->word);
		free(word_lst);
		word_lst = tmp;
	}
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
