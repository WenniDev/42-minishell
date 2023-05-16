#include "minishell.h"

void    exec_cmd_lst(t_data *msh, t_exec *e, t_command_lst *cl);
int		do_redir(t_exec *e, t_command cmd);
char	*get_path(t_data *msh, char *cmd_name);

/*static const t_builtin	g_builtin[] ={
		{"env", b_env}, {"pwd", b_pwd}, {"export", b_export},
		{"unset", b_unset}, {"echo", b_echo}, {"exit", b_exit}
};*/

char	**copy_word_list(t_word_lst *wl)
{
	t_word_lst	*elem;
	char		**argv;
	int			i;

	i = 0;
	elem = wl;
	while (elem)
	{
		elem = elem->next;
		i++;
	}
	argv = (char **)sfcalloc(i + 1, sizeof (char *));
	i = 0;
	elem = wl;
	while (elem)
	{
		argv[i] = elem->word->lval;
		elem = elem->next;
		i++;
	}
	return (argv);
}

/*int	execute_builtin(t_exec *e, t_command cmd)
{
	int			i;
	int			status;
	t_word_lst	*elem;

	i = 0;
	close_fds(e, 0);
	if (!cmd.elem.words->word->lval)
		return (EXIT_SUCCESS);
	cmd.argv = copy_word_lst(cmd.elem.words);
	while (ft_strcmp(cmd.argv[0], g_builtin[i].cmd))
		i++;
	status = g_builtin[i].ft(e, cmd.argc, cmd.argv);
	clean_argv(&cmd, cmd.argv);
	return (status);
}*/

int	execute_simple_cmd(t_data *msh, t_exec *e, t_command cmd)
{
/*	expand_word_lst(msh, &cl->cmd.elem.words);*/
	cmd.argv = copy_word_list(cmd.elem.words);
/*	if (cl->cmd.flags & CMD_BUILTIN)
		return (execute_builtin(e, cl->cmd));*/
	cmd.cmd_path = get_path(msh, cmd.elem.words->word->lval);
	execve(cmd.cmd_path, cmd.argv, e->env);
	msh_error(EREXECVE);
	return (EXIT_FAILURE);
}

void	create_child(t_exec *e)
{
	e->pid_curr = fork();
	if (e->pid_curr == -1)
		msh_error(ERFORK);
	if (e->pid_curr)
		e->pid_last = e->pid_curr;
	e->child_nb++;
}

int	check_exec(int f, pid_t pid_last)
{
	int	status;

	if (f & (CMD_EXECTRUE | CMD_EXECFALSE))
	{
		if (waitpid(pid_last, &status, 0) == -1)
			msh_error(ERWAITPID);
		if ((f & CMD_EXECFALSE && !WEXITSTATUS(status))
			|| (f & CMD_EXECTRUE && WEXITSTATUS(status)))
			return (EXS_NOEXEC);
	}
	return (EXS_SUCCESS);
}

int	exec_cmd(t_data *msh, t_exec *e, t_command cmd)
{
	if (cmd.flags & CMD_PIPE || !(cmd.flags & CMD_BUILTIN))
	{
		create_child(e);
		if (!msh->exec.pid_curr)
		{
			if (cmd.flags & CMD_SUBSHELL)
				exec_cmd_lst(msh, e, cmd.elem.cmds);
			else
				msh->status = execute_simple_cmd(msh, e, cmd);
			exit_prg(msh, msh->status);
		}
	}
	else
		 return (execute_simple_cmd(msh, e, cmd));
}

void    exec_cmd_lst(t_data *msh, t_exec *e, t_command_lst *cl)
{
	int	rtn_status;

	e->pipefd = (int *)sfcalloc(2, sizeof (int));
	do_ft(DUP, &e->tmpin, 0);
	do_ft(DUP, &e->tmpout, 1);
	while (cl)
	{
		if (check_exec(cl->cmd.flags, e->pid_last) || do_redir(e, cl->cmd))
		{
			cl = cl->next;
			continue ;
		}
		msh->status = exec_cmd(msh, e, cl->cmd);
		cl = cl->next;
	}
	do_ft(DUP2, &e->tmpin, 0);
	do_ft(DUP2, &e->tmpout, 1);
	if (e->child_nb)
	{
		if (waitpid(e->pid_last, &rtn_status, 0) == -1)
			msh_error(ERWAITPID);
		msh->status = WEXITSTATUS(rtn_status);
		while (--e->child_nb >= 0)
			if (wait(0) == -1)
				msh_error(ERWAIT);
	}
}
