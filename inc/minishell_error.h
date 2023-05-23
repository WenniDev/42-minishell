#ifndef MINISHELL_ERROR_H
#define MINISHELL_ERROR_H

# include "libft.h"
# include <signal.h>
# include <errno.h>

# define EXS_NOEXEC			(-2)
# define EXS_ERROR			(-1)
# define EXS_SUCCESS		0
# define EXS_SYNTAX_ERROR	2
# define EXS_EOF			130
# define EXS_SIGSEG			139

# define EUNEOL				"unexpected EOL while looking for matching `"
# define EREOF				"unexpected end of file"
# define ERTOK				"unexpected token: "

# define ERHOME				"HOME not set"

# define CMDNOTF			"command not found"
# define CMDPERMD			"permission denied"

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
int 	msh_error(char *error);
int		print_error(char *error, char *infos, char *infos2);

#endif
