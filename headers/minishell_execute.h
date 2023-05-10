#ifndef MINISHELL_EXECUTE_H
# define MINISHELL_EXECUTE_H

# include "minishell_command.h"

typedef struct s_exec
{
	pid_t	last_pid;
	int		fork_nb;
	int		status;
}t_exec;

#endif
