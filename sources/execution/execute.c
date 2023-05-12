#include "minishell.h"

/*static const t_builtin	g_builtin[] ={
		{"env", b_env},
		{"pwd", b_pwd},
		{"export", b_export},
		{"unset", b_unset},
		{"echo", b_echo},
		{"exit", b_exit}
};*/

void	init_fd_map(t_exec *e)
{
	e->fd_map[0] = dup(STDIN_FILENO);
	e->fd_map[1] = dup(STDOUT_FILENO);
	if (e->fd_map[0] == -1 || e->fd_map[1] == -1)
		msh_error(ERDUP);
}

void	close_fd_map(t_exec *e, int fd, int nb)
{
	while (nb > 0)
	{
		if (close(e->fd_map[fd]) == -1)
			msh_error(ERCLOSE);
		e->fd_map[fd] = 0;
		fd++;
		nb--;
	}
}

void	reset_stdfd(t_exec *e)
{
	if (dup2(e->fd_map[0], STDIN_FILENO) == -1
		|| dup2(e->fd_map[1], STDOUT_FILENO) == -1)
		msh_error(ERDUP2);
}

void	redirect(t_exec *e, t_red *r, int fdin, int fdout)
{
	e->fd_map[4] = fdin;
	e->fd_map[5] = fdout;
	while (r && !e->error)
	{
		if (r->rflags & RED_IN && e->fd_map[4])
			close_fd_map(e, 4, 1);
/*		if (r->rflags & RED_HEREDOC)
			e->fd_map[4] = heredoc(r->heredoc_eof);*/
		else if (r->rflags & RED_IN)
			e->fd_map[4] = open(r->filename->lval, r->oflags, 0664);
		if (r->rflags & RED_OUT && e->fd_map[5] > 1)
			close_fd_map(e, 5, 1);
		if (r->rflags & RED_OUT)
			e->fd_map[5] = open(r->filename->lval, r->oflags, 0664);
		if (e->fd_map[4] == -1 || e->fd_map[5] == -1)
			exit_prg()
	}
	if (dup2(e->fd_map[4], STDIN_FILENO) == -1
		|| dup2(e->fd_map[5], STDOUT_FILENO) == -1)
		msh_error(ERDUP2);
	close_fd_map(e, 4, 2);
}

void	execute_simple_cmd(t_data *msh, t_exec *e, t_command cmd)
{
	int	last_cmd_status;

	close_fd_map(e, 0, 7);
	if (cmd.flags & CMD_EXECFALSE || cmd.flags & CMD_EXECTRUE)
		if (waitpid(e->pid_last, &last_cmd_status, 0) == -1)
			msh_error(ERWAITPID);
	e->cmd_path = get_path(e, cmd.elem.words->word);
	if (!e->cmd_path)
		exit_prg(e->error);
	e->argv = copy_word_lst(cmd.elem.words);
	if (execve(cmd_path, e->argv, e->env) == -1)
		msh_error(EREXECVE);
}

void	execute_cmd(t_data *msh, t_exec *e, t_command cmd, int fdin , int fdout)
{
/*	if (cmd.flags & CMD_BUILTIN && !(cmd.flags & CMD_PIPE))
		return (execute_builtin_cmd(e, cmd));*/
	e->pid_curr = fork();
	if (e->pid_curr == -1)
		msh_error(ERFORK);
	if (!e->pid_curr)
	{
		redirect(e, cmd.reds, fdin, fdout);
/*		if (cmd.flags & CMD_SUBSHELL)
			return (execute_in_subshell(e, cmd));*/
/*		else if (cmd.flags & CMD_BUILTIN)
			return (execute_builtin_cmd(e, cmd));*/
		if (cmd.flags & CMD_SIMPLE)
			return (execute_simple_cmd(msh, e, cmd));
	}
	else
	{
		e->pid_last = e->pid_curr;
		e->to_wait++;
	}
	reset_stdfd(e);
}

int	execute_cmds_lst(t_data *msh, t_exec *e, t_command_lst *cl)
{
	init_fd_map(e);
	while (cl)
	{
		if (pipe(e->fd_map + 2) == -1)
			msh_error(ERPIPE);
		if (cl->cmd.flags & CMD_STARTPIPE)
			execute_cmd(msh, e, cl->cmd, e->fd_map[0], e->fd_map[3]);
		else if (cl->cmd.flags & CMD_ENDPIPE)
			execute_cmd(msh, e, cl->cmd, e->fd_map[2], e->fd_map[1]);
		else if (cl->cmd.flags & CMD_PIPE)
			execute_cmd(msh, e, cl->cmd, e->fd_map[2], e->fd_map[3]);
		else
			execute_cmd(msh, e, cl->cmd, e->fd_map[0], e->fd_map[1]);
		cl = cl->next;
	}
	return (e->status);
}
