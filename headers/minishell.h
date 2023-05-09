#ifndef MINISHELL_TYPES_H
# define MINISHELL_TYPES_H

# include "minishell_command.h"
# include "minishell_parse.h"
# include "minishell_error.h"
# include "libft.h"
# include <signal.h>

typedef u_int8_t t_bool;

typedef struct s_data
{
	t_parser	parser;
	int			status;
}t_data;

void	signal_handler(t_data *msh);
int		parse(t_parser *p, t_bool reset);

#endif
