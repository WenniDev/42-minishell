//	NORM
//		-missing header

#ifndef SPASH_ERROR_H
# define SPASH_ERROR_H

# define MFAIL		"Malloc failed"
# define UNEOF		"Unexpected end of file"

void	sperr(t_data *data, char *msg, char *infos, int errnum);
void	put_sperr(t_error error);

#endif