//	NORM
//		-missing header

#ifndef SPASH_BUILTINS_H
# define SPASH_BUILTINS_H

# include "spash_types.h"
# include "spash_error.h"
# include <unistd.h>
# include <stdlib.h>

int	b_cd(int argc, char **argv, void *ptr);
int	b_env(int argc, char **argv, void *ptr);
int	b_pwd(int argc, char **argv, void *data);

#endif