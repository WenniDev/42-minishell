/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expand.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:56:24 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/11 13:46:13 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXPAND_H
# define MINISHELL_EXPAND_H

# include "minishell_command.h"

int		expand(t_command_lst *commands);
void	expand_env(t_word_d *word, int *status);

#endif
