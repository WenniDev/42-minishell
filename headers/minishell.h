#ifndef MINISHELL_TYPES_H
# define MINISHELL_TYPES_H

# include "minishell_command.h"
# include "minishell_parse.h"
# include "minishell_execute.h"
# include "minishell_error.h"
# include "libft.h"
# include <signal.h>

typedef struct s_data
{
	t_parser	parser;
	t_exec		exec;
	int			status;
}t_data;

void	signal_handler(t_data *msh);
int		parse(t_parser *p);

#endif
