/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expand.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:56:24 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/12 18:45:15 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXPAND_H
# define MINISHELL_EXPAND_H

# include "minishell_command.h"

#define M_DEFAULT 0x00
#define M_SINGLE 0x01
#define M_DOUBLE 0x02

int		expand(t_word_lst *wold_lst);
void	expand_env(t_word_d *word, int *status);
void	expand_wildcard(t_word_lst **word_lst, int *status);

#endif
