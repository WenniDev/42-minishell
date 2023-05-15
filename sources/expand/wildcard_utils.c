/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:34:32 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/15 16:55:09 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_command.h"
#include <dirent.h>
#include <sys/stat.h>
#include "libft.h"

void	insert_list(t_word_lst **word_lst, t_word_lst *tmp)
{
	t_word_lst	*next_word;
	t_word_lst	*begin_tmp;

	if (!tmp)
		return ;
	if (*word_lst == NULL)
		*word_lst = tmp;
	else
	{
		next_word = (*word_lst)->next;
		begin_tmp = tmp;
		while (begin_tmp->next)
			begin_tmp = begin_tmp->next;
		begin_tmp->next = next_word;
		free((*word_lst)->word->lval);
		free((*word_lst)->word);
//		free((*word_lst)); //Error when free (?)
		**word_lst = *tmp;
	}
}

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
