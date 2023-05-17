#ifndef MINISHELL_BUILTINS_H
# define MINISHELL_BUILTINS_H

# include "minishell_execute.h"
# include "minishell_error.h"
# include <errno.h>
# include <string.h>

int	b_env(t_exec *e, int argc, char **argv);
int	b_pwd(t_exec *e, int argc, char **argv);
int	b_cd(t_exec *e, int argc, char **argv);
int	b_unset(t_exec *e, int argc, char **argv);

#endif
