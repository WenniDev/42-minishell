/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:40:02 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:40:23 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_env.h"
# include "minishell_command.h"
# include "minishell_parse.h"
# include "minishell_execute.h"
# include "minishell_redirect.h"
# include "minishell_error.h"
# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_data
{
	t_parser	parser;
	int			parser_status;
	t_exec		exec;
	int			status;
	char		*xpwd;
}t_data;

void	signal_handler(t_data *msh);
int		parse(t_parser *p);
int		exit_prg(t_data *msh, int status);
void	clean_all(t_data *msh);
void	set_prompt(t_data *msh);

#endif
