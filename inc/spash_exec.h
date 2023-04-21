//	NORM
//		-missing header

#ifndef SPASH_EXEC_H
# define SPASH_EXEC_H

# define IN		0
# define OUT	1
# define PIPE0	2
# define PIPE1	3

int		exec(t_data *data);
void	io_red(t_data *data, int i);

#endif
