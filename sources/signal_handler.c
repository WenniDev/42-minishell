#include "minishell.h"

t_data	*g_msh;

void	reset_parser(t_parser *p);

void	handle_sigabrt(int signum)
{
	(void)signum;
	ft_putstr_fd(ABRTMSG, 2);
	ft_putchar_fd('\n', 2);
	reset_parser(&g_msh->parser);
	exit(EXIT_FAILURE);
}

void	signal_handler(t_data *msh)
{
	g_msh = msh;
	signal(SIGABRT, handle_sigabrt);
//	signal(SIGINT, handle_sigint);
//	signal(SIGQUIT, handle_sigquit);
}
