#ifndef MINISHELL_ERROR_H
#define MINISHELL_ERROR_H

# include "libft.h"
# include <signal.h>
# include <errno.h>

# define EXS_ERROR			(-1)
# define EXS_SUCCESS		0
# define EXS_SYNTAX_ERROR	2
# define EXS_EOF			130
# define EXS_SIGSEG			139

# define EUNEOL				"unexpected EOL while looking for matching `"
# define EMFAILED			"Malloc failed"
# define EREOF				"unexpected end of file"
# define ERTOK				"unexpected token: "
# define ERDUP				"dup failed"
# define ERPIPE				"pipe failed"
# define ERDUP2				"dup2 failed"
# define ERFORK				"fork failed"
# define EROPEN				"open failed"
# define ERCLOSE			"close failed"

# define ABRTMSG			"sigabrt"

int		quote_error(char quote);
int		malloc_error(void);
int		syntax_error(char *error, int tk, char *lval);
void	msh_error(char *error);

#endif
