#include "minishell.h"
#include "minishell_parse.h"

t_data	*g_msh;

void	handle_sigabrt(int signum)
{
	(void)signum;
	clean_all(g_msh);
	exit(EXS_SIGSEG);
}

void	handle_sig(int signum)
{
	if (g_msh->exec.child_nb)
	{
		if (g_msh->exec.pid_curr)
			signal(SIGTERM, SIG_IGN);
		if (signum == SIGQUIT)
				printf("%s", QUITMSG);
		printf("\n");
		kill(0, SIGTERM);
	}
	else
	{
		if (signum == SIGINT)
			printf("\n");
		if (signum == SIGQUIT)
			printf("\r\e[K");
		rl_on_new_line();
		if (signum == SIGINT)
			rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler(t_data *msh)
{
	g_msh = msh;
	signal(SIGABRT, handle_sigabrt);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
}
