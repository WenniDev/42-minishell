/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:12:39 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/27 11:02:48 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_expand.h"

int		mod_redir(int status, t_exec *e, t_red *r);
void	do_pipe_red(t_exec *e, t_command cmd);

int	do_redir(int status, t_exec *e, t_command cmd)
{
	do_ft(DUP2, &e->tmpin, STDIN_FILENO);
	do_ft(DUP2, &e->tmpout, STDOUT_FILENO);
	if (cmd.flags & CMD_PIPE)
		do_pipe_red(e, cmd);
	while (cmd.reds)
	{
		if (mod_redir(status, e, cmd.reds))
			return (e->status = 1);
		cmd.reds = cmd.reds->next;
	}
	if (e->infd)
	{
		do_ft(DUP2, &e->infd, STDIN_FILENO);
		do_ft(CLOSE, &e->infd, 0);
	}
	if (e->outfd)
	{
		do_ft(DUP2, &e->outfd, STDOUT_FILENO);
		do_ft(CLOSE, &e->outfd, 0);
	}
	return (0);
}

void	do_pipe_red(t_exec *e, t_command cmd)
{
	if (!(cmd.flags & CMD_STARTPIPE))
	{
		do_ft(DUP2, &e->pipefd[0], STDIN_FILENO);
		do_ft(CLOSE, &e->pipefd[0], 0);
	}
	if (!(cmd.flags & CMD_ENDPIPE))
	{
		do_ft(PIPE, e->pipefd, 0);
		e->outfd = e->pipefd[1];
	}
}

int	mod_redir(int status, t_exec *e, t_red *r)
{
	if (r->filename->lval && !expand_red(status, r->filename))
		return (print_error(REDAMB, r->filename->lval, NULL));
	if (r->rflags & RED_IN)
	{
		if (e->infd)
			do_ft(CLOSE, &e->infd, 0);
		if (r->rflags & RED_HEREDOC)
			e->infd = here_document_to_fd(r, status);
		else
			e->infd = open(r->filename->lval, r->oflags, 0664);
		if (e->infd == -1)
			return (print_error(strerror(errno), r->filename->lval, NULL));
	}
	if (r->rflags & RED_OUT)
	{
		if (e->outfd)
			do_ft(CLOSE, &e->outfd, 0);
		e->outfd = open(r->filename->lval, r->oflags, 0664);
		if (e->outfd == -1)
			return (print_error(strerror(errno), r->filename->lval, NULL));
	}
	return (0);
}

void	set_fds(t_exec *e, int flag)
{
	if (!flag)
	{
		if (!e->pipefd)
			e->pipefd = (int *)sfcalloc(2, sizeof (int));
		do_ft(DUP, &e->tmpin, 0);
		do_ft(DUP, &e->tmpout, 1);
	}
	if (flag == 1)
	{
		do_ft(DUP2, &e->tmpin, 0);
		do_ft(DUP2, &e->tmpout, 1);
		do_ft(CLOSE, &e->tmpin, 0);
		do_ft(CLOSE, &e->tmpout, 0);
	}
	if (flag > 1)
	{
		e->infd = 0;
		e->outfd = 0;
	}
}

void	close_all(t_exec *e)
{
	do_ft(CLOSE, &e->tmpin, 0);
	do_ft(CLOSE, &e->tmpout, 0);
	do_ft(CLOSE, &e->infd, 0);
	do_ft(CLOSE, &e->outfd, 0);
	do_ft(CLOSE, &e->pipefd[0], 0);
}
