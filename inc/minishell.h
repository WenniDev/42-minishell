#ifndef MINISHELL_TYPES_H
# define MINISHELL_TYPES_H

# include "minishell_env.h"
# include "minishell_command.h"
# include "minishell_parse.h"
# include "minishell_execute.h"
# include "minishell_redirect.h"
# include "minishell_error.h"
# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_data
{
	t_parser	parser;
	t_exec		exec;
	int			status;
}t_data;

void	signal_handler(t_data *msh);
int		parse(t_parser *p);
int		exit_prg(t_data *msh, int status);
void	clean_all(t_data *msh);
void	set_prompt(t_data *msh);

#endif
