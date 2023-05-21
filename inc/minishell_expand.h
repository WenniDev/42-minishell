/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expand.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:56:24 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/21 16:31:43 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXPAND_H
# define MINISHELL_EXPAND_H

# include "minishell_command.h"
# include <dirent.h>

#define M_DEFAULT 0x00
#define M_SINGLE 0x01
#define M_DOUBLE 0x02

int		expand(t_word_lst **wold_lst);
void	expand_env(t_word_d *word, int *status);
void	expand_wildcard(t_word_d *word, t_word_lst **word_lst, int *status);
void	*expand_red(t_word_d *filename);

int		is_dir(struct dirent *ent);
void	insert_list(t_word_d *word, t_word_lst **word_lst, t_word_lst **tmp);
void	free_word_lst(t_word_lst *word_lst);
void	free_word(t_word_d *word);
int		is_dir_pattern(char *pattern);

#endif
