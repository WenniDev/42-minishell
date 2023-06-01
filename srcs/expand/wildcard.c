/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:28:31 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/30 22:33:42 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_command.h"
#include "minishell_expand.h"
#include <dirent.h>
#include "libft.h"

static int	match_wc(char *name, char *pattern)
{
	if (!name || !pattern)
		return (0);
	if (*name && *pattern == '*')
		return (match_wc(name, pattern + 1) || match_wc(name + 1, pattern));
	if (!*name && (*pattern == '*' || *pattern == '/'))
		return (match_wc(name, pattern + 1));
	if (*pattern == *name && *name && *pattern)
		return (match_wc(name + 1, pattern + 1));
	if (*pattern == *name && !*name && !*pattern)
		return (1);
	return (0);
}

static int	match_pattern(char *pattern, struct dirent *ent, int look_for_dir)
{
	if (!ent || (*(ent->d_name) == '.' && *pattern == '*'))
		return (0);
	if (ft_strncmp(ent->d_name, ".", 1) == 0
		&& ft_strncmp(pattern, "*", ft_strlen(pattern)) == 0)
		return (0);
	if (look_for_dir && !is_dir(ent))
		return (0);
	return (1);
}

void	add_in_list(t_word_lst **files, t_word_lst *word)
{
	t_word_lst	*last_node;

	if (*files == NULL)
		*files = word;
	else
	{
		last_node = (*files);
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = word;
	}
}

static void	*add_file(t_word_lst **word_lst, int is_dir, struct dirent *ent)
{
	t_word_lst	*new_file;

	new_file = ft_calloc(1, sizeof(t_word_lst));
	if (!new_file)
		return (0);
	new_file->word = ft_calloc(1, sizeof(t_word_d));
	if (!new_file->word)
		return (0);
	if (is_dir)
		new_file->word->lval = ft_strjoin(ent->d_name, "/");
	else
		new_file->word->lval = ft_strdup(ent->d_name);
	if (!new_file->word->lval)
		return (0);
	new_file->word->flags = W_NOEXPAND;
	new_file->next = NULL;
	add_in_list(word_lst, new_file);
	return (new_file);
}

void	expand_wildcard(t_word_d *word, t_word_lst **word_lst, int *status)
{
	DIR				*dir;
	struct dirent	*ent;
	int				look_for_dir;
	t_word_lst		*tmp_lst;

	dir = opendir(".");
	if (!dir)
		return (*status = 1, (void) NULL);
	ent = (void *)1;
	tmp_lst = NULL;
	look_for_dir = is_dir_pattern(word->lval);
	while (ent)
	{
		ent = readdir(dir);
		if (!match_pattern(word->lval, ent, look_for_dir))
			continue ;
		if (!match_wc(ent->d_name, word->lval))
			continue ;
		if (!add_file(&tmp_lst, look_for_dir, ent))
			return (*status = 1, closedir(dir), free_word_lst(tmp_lst));
	}
	insert_list(word, word_lst, &tmp_lst);
	return (*status = 0, (void)closedir(dir));
}
