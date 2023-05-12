#ifndef MINISHELL_EXECUTE_H
# define MINISHELL_EXECUTE_H

# include "minishell_command.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_exec
{
	char			*cmd_path;
	char			**argv;
	char			**env;
	int				fd_map[7];
	pid_t			pid_curr;
	pid_t			pid_last;
	int				to_wait;
	int				error;
	int				status;
}t_exec;

typedef struct s_builtin
{
	char	*cmd;
	int		(*ft)(t_exec *e, int argc, char **argv);
}t_builtin;

#endif
