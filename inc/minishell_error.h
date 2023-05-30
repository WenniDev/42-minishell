/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:38:42 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:38:53 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

# include "libft.h"
# include <signal.h>
# include <errno.h>
# include <string.h>

# define EXS_NOEXEC			(-2)
# define EXS_ERROR			(-1)
# define EXS_SUCCESS		0
# define EXS_SYNTAX_ERROR	2
# define EXS_EOF			130
# define EXS_SIGSEG			139

# define EUNEOL				"unexpected EOL while looking for matching `"
# define EREOF				"unexpected end of file"
# define ERTOK				"unexpected token: "
# define ERHDMAX			"maximum here-document count exceeded"

# define ERHOME				"HOME not set"
# define EXPFAIL			"not a valid identifier"
# define ERARGC				"too many arguments"
# define ERNUMARG			"numeric argument required"

# define CMDNOTF			"command not found"

# define REDAMB				"ambiguous redirect"

# define EMFAILED			"Malloc failed"
# define ERDUP				"dup failed"
# define ERPIPE				"pipe failed"
# define ERDUP2				"dup2 failed"
# define ERFORK				"fork failed"
# define ERCLOSE			"close failed"
# define ERWAITPID			"waitpid failed"
# define EREXECVE			"execve failed"
# define ERWAIT				"wait failed"

# define QUITMSG			"Quit (core dumped)"

int		quote_error(char quote);
int		malloc_error(void);
int		syntax_error(char *error, int tk, char *lval);
int		msh_error(char *error);
int		print_error(char *error, char *infos, char *infos2);

#endif
