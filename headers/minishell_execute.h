#ifndef MINISHELL_EXECUTE_H
# define MINISHELL_EXECUTE_H

# include "minishell_command.h"
# include <unistd.h>

typedef struct s_exec
{
	int		fd_map[6];
	pid_t	pid_curr;
	pid_t	pid_last;
	int		fork_nb;
	int		status;
}t_exec;

#endif
