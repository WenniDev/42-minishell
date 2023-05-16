#include "minishell.h"

int	mod_redir(t_exec *e, t_red *r);

int	do_redir(t_exec *e, t_command cmd)
{
	do_ft(DUP2, &e->infd, 0);
	do_ft(CLOSE, &e->infd, 0);
	if (cmd.flags & CMD_STARTPIPE || !(cmd.flags & CMD_PIPE))
		do_ft(DUP, &e->infd, e->tmpin);
	if (cmd.flags & CMD_ENDPIPE || !(cmd.flags & CMD_PIPE))
		do_ft(DUP, &e->outfd, e->tmpout);
	if (cmd.flags & CMD_PIPE)
	{
		do_ft(PIPE, e->pipefd, 0);
		e->infd = e->pipefd[0];
		e->outfd = e->pipefd[1];
	}
	while (cmd.reds)
	{
		if (mod_redir(e, cmd.reds))
			return (-1);
		cmd.reds = cmd.reds->next;
	}
	if (e->infd)
		do_ft(DUP2, &e->infd, 0);
	do_ft(DUP2, &e->outfd, 1);
	do_ft(CLOSE, &e->outfd, 0);
	return (0);
}

int	mod_redir(t_exec *e, t_red *r)
{
	if (r->rflags & RED_IN)
	{
		if (e->infd)
			do_ft(CLOSE, &e->infd, 0);
		if (r->rflags & RED_HEREDOC)
			e->infd = heredoc(r);
		else
			e->infd = open(r->filename->lval, r->oflags, 0664);
		if (e->infd == -1)
			return (print_error(strerror(errno), r->filename->lval));

	}
	if (r->rflags & RED_OUT)
	{
		if (e->outfd)
			do_ft(CLOSE, &e->outfd, 0);
		e->outfd = open(r->filename->lval, r->oflags, 0664);
		if (e->outfd == -1)
			return (print_error(strerror(errno), r->filename->lval));
	}
}
