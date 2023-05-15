#include "minishell.h"

int	change_red(t_exec *e, t_red *r);

void	close_fds(t_exec *e, bool all)
{
	if ((e->infd > 0 && close(e->infd) == -1)
		|| (e->outfd > 1 && close(e->outfd) == -1)
		|| (all && e->pipefd[0] > 0 && close(e->pipefd[0]) == -1)
		|| (all && e->pipefd[1] > 0 && close(e->pipefd[1]) == -1))
		msh_error(ERCLOSE);
	e->infd = 0;
	e->outfd = 0;
	if (all)
		ft_memset(e->pipefd, 0, sizeof (e->pipefd));
}

int	do_redirection(t_exec *e, t_command cmd)
{
	t_red	*r;
	int		red_error;

	red_error = 0;
	e->infd = STDIN_FILENO;
	e->outfd = STDOUT_FILENO;
	if (cmd.flags & CMD_PIPE && !(cmd.flags & CMD_STARTPIPE))
		e->infd = e->pipefd[0];
	else if (cmd.flags & CMD_PIPE && !(cmd.flags & CMD_ENDPIPE))
		e->outfd = e->pipefd[1];
	r = cmd.reds;
	while (r && !red_error)
	{
		red_error = change_red(e, r);
		r = r->next;
	}
	return (red_error);
}

int	change_red(t_exec *e, t_red *r)
{
/*	if (!expand_red(r))
		return (print_error(ERAMBRED, r->filename->lval), EXS_ERROR);*/
	if (r->rflags & RED_OUT)
	{
		if (e->outfd && close(e->outfd) == -1)
			msh_error(ERCLOSE);
		e->outfd = open(r->filename->lval, r->oflags, 0664);
	}
	if (r->rflags & RED_IN)
	{
		if (e->infd && close(e->infd) == -1)
			msh_error(ERCLOSE);
/*		if (r->rflags & RED_HEREDOC)
			e->infd = heredoc(msh, e, r);*/
		else
			e->infd = open(r->filename->lval, r->oflags, 0664);
	}
	if (e->infd == -1 || e->outfd == -1)
		return (print_error(strerror(errno), r->filename->lval), EXS_ERROR);
	return (EXS_SUCCESS);
}
