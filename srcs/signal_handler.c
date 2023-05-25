#include "minishell.h"
#include "minishell_parse.h"

t_data	*g_msh;

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

void	handle_sigabrt(int signum)
{
	(void)signum;
	clean_all(g_msh);
	exit(EXS_SIGSEG);
}

void	handle_sigint(int signum)
{
	if (g_msh->parser.state & PST_HEREDOC)
	{
		printf("\n");
		close(STDIN_FILENO);
	}
	if (g_msh->exec.child_nb)
	{
		if (g_msh->exec.child == false)
			signal(SIGTERM, SIG_IGN);
		printf("\n");
		kill(0, SIGTERM);
	}
	else if (!(g_msh->parser.state & PST_HEREDOC))
		redisplay(signum);
	g_msh->status = 130;
	g_msh->parser.state &= ~PST_HEREDOC;
}

void	handle_sigquit(int signum)
{
	if (g_msh->exec.child_nb)
	{
		if (g_msh->exec.child == false)
			signal(SIGTERM, SIG_IGN);
		printf("%s", QUITMSG);
		printf("\n");
		kill(0, SIGTERM);
	}
	else
		redisplay(signum);
	g_msh->status = 131;
}

void	signal_handler(t_data *msh)
{
	g_msh = msh;
	signal(SIGABRT, handle_sigabrt);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
