//	NORM
//		-missing header

#ifndef SPASH_EXEC_H
# define SPASH_EXEC_H

# include "spash_types.h"
# include <stdbool.h>

# define IN				0
# define OUT			1
# define PIPE0			2
# define PIPE1			3

# define S_EXPORT		"export"
# define S_PWD			"pwd"
# define S_UNSET		"unset"
# define S_CD			"cd"
# define S_EXIT			"exit"
# define S_ECHO			"echo"
# define S_ENV			"env"

# define I_EXPORT		0
# define I_PWD			1
# define I_UNSET		2
# define I_CD			3
# define I_EXIT			4
# define I_ECHO			5
# define I_ENV			6

int		exec(t_data *data);
void	io_red(t_data *data, int i);
int		exec_builtin(t_data *data, t_cmd cmd);
void	exec_cmd(t_data *data, t_cmd cmd, bool exec);

#endif
