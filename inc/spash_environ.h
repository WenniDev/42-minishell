//	NORM
//		-missing header
//	TODO
//		-fixe tabs in DEFAULT_PATH

#ifndef SPASH_ENVIRON_H
# define SPASH_ENVIRON_H

# include "spash_types.h"
# include "libft.h"

# define DEFAULT_ENV	"PATH=NULL:PWD=NULL:PS1=>:SHLVL=0:_=NULL"
# define DEFAULT_PATH	"PATH=/usr/local/sbin:\
						/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define ENV_SEP		":"

void	init_env(t_data *data);

#endif
