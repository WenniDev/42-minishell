/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:28:31 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/12 19:49:11 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_command.h"
#include "minishell_expand.h"
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>
#include "libft.h"
#include "stdio.h"

#define debug_print(fmt, ...) \
        do { fprintf(stderr, "\e[1;34m%s\e[1;0m:\e[1;32m%d\e[1;0m:\e[1;0m\e[1;36m%s()\e[1;0m:	" fmt, __FILE_NAME__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

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

int	is_dir(struct dirent *ent)
{
	struct stat	info;

	if (stat(ent->d_name, &info) != 0)
		return (0);
	if (S_ISDIR(info.st_mode))
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
		last_node = *files;
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
	if (!new_file->word)
		return (0);
	new_file->next = NULL;
	add_in_list(word_lst, new_file);
	return (new_file);
}


// test* lol => test* test1 test2 test3 test4 lol

void	insertList(t_word_lst **word_lst, t_word_lst *tmp)
{
	t_word_lst	*next_word;
	t_word_lst	*begin_tmp;

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

void	expand_wildcard(t_word_lst **word_lst, int *status)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*pattern;
	int				look_for_dir;
	t_word_lst		*tmp_lst;

	debug_print("word with wildcard: %s\n", (*word_lst)->word->lval);
	dir = opendir(".");
	if (!dir)
		return (*status = 1, (void) NULL);
	ent = (void *)1;
	tmp_lst = NULL;
	pattern = (*word_lst)->word->lval;
	if (*pattern && pattern[ft_strlen(pattern) - 1] == '/')
		look_for_dir = 1;
	else
		look_for_dir = 0;
	while (ent)
	{
		ent = readdir(dir);
		if (!match_pattern(pattern, ent, look_for_dir))
			continue ;
		if (!match_wc(ent->d_name, pattern))
			continue ;
		if (!add_file(&tmp_lst, look_for_dir, ent))
			return ((void)closedir(dir));
	}
	if (tmp_lst)
		insertList(word_lst, tmp_lst);
	*status = 0;
}