#ifndef MINISHELL_REDIRECT_H
# define MINISHELL_REDIRECT_H

# include <stdbool.h>

# define CLOSE	1
# define DUP	2
# define DUP2	3
# define PIPE	4

void	close_all(t_exec *e);
int		do_redir(t_exec *e, t_command cmd);
void 	set_fds(t_exec *e, int flag);

#endif