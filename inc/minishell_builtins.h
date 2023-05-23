/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:01:44 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/23 18:26:30 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTINS_H
# define MINISHELL_BUILTINS_H

# include "minishell_execute.h"
# include "minishell_error.h"
# include <errno.h>
# include <string.h>

typedef struct s_echo
{
	int	word;
	int	no_new_line;
	int	param_end;
}	t_echo;

int	b_env(t_exec *e, int argc, char **argv);
int	b_pwd(t_exec *e, int argc, char **argv);
int	b_cd(t_exec *e, int argc, char **argv);
int	b_unset(t_exec *e, int argc, char **argv);
int	b_echo(t_exec *e, int argc, char **argv);
int	b_export(t_exec *e, int argc, char **argv);

void	export_var(char *name, char *value, t_exec *e);
void	unset_var(t_exec *e, char *var);

#endif
