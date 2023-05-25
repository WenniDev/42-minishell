#include "minishell.h"
#include "minishell_parse.h"

t_data	*g_msh;

void	handle_sigabrt(int signum)
{
	(void)signum;
	clean_all(g_msh);
	exit(EXS_SIGSEG);
}

void	redisplay(int signum)
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

void	handle_sig(int signum)
{
	if (signum == SIGINT && g_msh->parser.state & PST_HEREDOC)
		close(0);
	if (g_msh->exec.child_nb)
	{
		if (g_msh->exec.child == false)
			signal(SIGTERM, SIG_IGN);
		if (signum == SIGQUIT)
				printf("%s", QUITMSG);
		printf("\n");
		kill(0, SIGTERM);
	}
	else
		redisplay(signum);
	if (signum == SIGINT)
		g_msh->status = 130;
	if (signum == SIGQUIT)
		g_msh->status = 131;
	if (signum == SIGINT)
		g_msh->parser.state &= ~PST_HEREDOC;
}

void	signal_handler(t_data *msh)
{
	g_msh = msh;
	signal(SIGABRT, handle_sigabrt);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
}
