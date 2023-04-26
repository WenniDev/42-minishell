//	NORM
//		-missing header

#ifndef SPASH_ERROR_H
# define SPASH_ERROR_H

# include "spash_types.h"
# include <errno.h>

# define MFAIL		"Malloc failed"
# define UNEOF		"syntax error: unexpected end of file"
# define UNCQUOTE	"unexpected EOL while looking for matching"
# define UNTOK		"syntax error: unexpected token"
# define CMDNOTF	"command not found"
# define PERMDN		"permission denied"
# define CDFAIL		"HOME not set"
# define PWDFAIL	"OLDPWD not set"
# define CDTMARG	"too many arguments"

# define ERROR		(-1)

void	sperr(t_data *data, char *msg, char *infos, int errnum);
void	put_sperr(t_error error);
void	uncquote_error(t_data *data, char quote);

#endif