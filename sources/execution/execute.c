#include "minishell_execute.h"
#include "minishell_redirect.h"
#include "minishell_error.h"

void	init_fd_map(t_exec *e)
{
	e->fd_map[0] = dup(STDIN_FILENO);
	e->fd_map[1] = dup(STDOUT_FILENO);
	if (e->fd_map[0] == -1 || e->fd_map[1] == -1)
		msh_error(ERDUP);
}

void	do_red(t_exec *e, t_red *red)
{
	if (red->heredoc_eof)
		e->fd_map[4] = get_heredoc(e, red);
	else if (red->src == 0)
	{
		e->fd_map[4] = open(red->filename->lval, red->oflags, 0664);
		if (e->fd_map[4] == -1)
			msh_error(EROPEN);
	}
	if (red->src == 1)
	{
		e->fd_map[5] = open(red->filename->lval, red->oflags, 0664);
		if (e->fd_map[5] == -1)
			msh_error(EROPEN);
		if (red->next)
			close(e->fd_map[5]);
	}
}

void	redirect(t_exec *e, t_command cmd)
{
	e->fd_map[4] = dup(e->fd_map[0]);
	e->fd_map[5] = dup(e->fd_map[1]);
	if (e->fd_map[4] == -1 || e->fd_map[5] == -1)
		msh_error(ERDUP);
	if (cmd.flags & CMD_PIPE && !(cmd.flags & CMD_STARTPIPE))
	{
		close(e->fd_map[4]);
		e->fd_map[4] = e->fd_map[2];
	}
	if (cmd.flags & CMD_PIPE && !(cmd.flags & CMD_ENDPIPE))
	{
		close(e->fd_map[5]);
		e->fd_map[5] = e->fd_map[3];
	}
	while (cmd.reds)
	{
		do_red(e, cmd.reds);
		cmd.reds = cmd.reds->next;
	}
	if (dup2(e->fd_map[4], STDIN_FILENO) == -1
		|| dup2(e->fd_map[5], STDOUT_FILENO) == -1)
		msh_error(ERDUP2);
}

int	execute(t_exec *e, t_command_lst *cmds)
{
	init_fd_map(e);
	while (cmds->next)
	{
		redirect(e, cmds->cmd);
		if (cmds->cmd.type == subshell_cmd)
			execute_in_subshell(e, cmds->cmd);
		else
			execute_simple_cmd(e, cmds->cmd);
		cmds = cmds->next;
	}
	return (e->status);
}
