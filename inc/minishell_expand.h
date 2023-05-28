/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expand.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:56:24 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/28 20:30:31 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXPAND_H
# define MINISHELL_EXPAND_H

# include "minishell_command.h"
# include <dirent.h>

# define M_DEFAULT	0x00
# define M_SINGLE	0x01
# define M_DOUBLE	0x02

int		expand(int status, t_word_lst **wold_lst);
void	expand_env(t_word_d *word, int *status, int ls);
void	word_splitting(t_word_d *word, t_word_lst **word_lst, int *status);
void	*expand_red(int ls, t_word_d *filename);
char	*here_document_expand(int ls, t_red *r, int *len);
void	expand_wildcard(t_word_d *word, t_word_lst **word_lst, int *status);
void	skip_quotes(char *word);

int		is_dir(struct dirent *ent);
void	insert_list(t_word_d *word, t_word_lst **word_lst, t_word_lst **tmp);
void	add_in_list(t_word_lst **files, t_word_lst *word);
void	free_word_lst(t_word_lst *word_lst);
void	free_word(t_word_d *word);
int		is_dir_pattern(char *pattern);
char	*ft_strpbrk(char *str1, char *str2);

int		expand_special(t_word_d *word);

#endif
