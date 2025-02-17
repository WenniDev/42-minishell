/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:01:44 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/27 10:38:08 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTINS_H
# define MINISHELL_BUILTINS_H

# include "minishell_execute.h"
# include "minishell_error.h"
# include "sys/types.h"
# include "sys/stat.h"
# include <errno.h>
# include <string.h>

typedef struct s_echo
{
	int	word;
	int	no_new_line;
	int	param_end;
}	t_echo;

int		b_env(void *data, t_word_lst *wl, int wnb);
int		b_pwd(void *data, t_word_lst *wl, int wnb);
int		b_cd(void *data, t_word_lst *wl, int wnb);
int		b_unset(void *data, t_word_lst *wl, int wnb);
int		b_echo(void *data, t_word_lst *wl, int wnb);
int		b_export(void *data, t_word_lst *wl, int wnb);
int		b_exit(void *data, t_word_lst *wl, int wnb);

void	export_var(char *name, char *value, t_exec *e);
void	unset_var(t_exec *e, char *var);

#endif
