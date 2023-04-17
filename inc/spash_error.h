//	NORM
//		-missing header

#ifndef SPASH_ERROR_H
# define SPASH_ERROR_H

# define MFAIL		"Malloc failed"
# define UNEOF		"syntax error: unexpected end of file"
# define UNCQUOTE	"syntax error: unclosed quote"
# define UNTOK		"syntax error: unexpected token"

void	sperr(t_data *data, char *msg, char *infos, int errnum);
void	put_sperr(t_error error);
void	uncquote_error(t_data *data, char quote);

#endif