#include "minishell.h"

int		execute_cmd_lst(t_data *msh, t_command_lst *cl);
int		do_redirection(t_exec *e, t_command cmd);
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
*//*	clean_argv(&cmd, cmd.argv);*//*
	return (status);
}*/

int	execute_simple_cmd(t_data *msh, t_exec *e, t_command_lst *cl)
{
/*	expand_word_lst(msh, &cl->cmd.elem.words);*/
	cl->cmd.argv = copy_word_list(cl->cmd.elem.words);
/*	if (cl->cmd.flags & CMD_BUILTIN)
		return (execute_builtin(e, cl->cmd));*/
	cl->cmd.cmd_path = get_path(msh, cl->cmd.elem.words->word->lval);
	execve(cl->cmd.cmd_path, cl->cmd.argv, e->env);
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

int	check_exec(t_exec *e, t_command_lst *cl)
{
	int	status;

	if (cl->cmd.flags & (CMD_EXECTRUE | CMD_EXECFALSE))
	{
		if (waitpid(e->pid_last, &status, 0) == -1)
			msh_error(ERWAITPID);
		if ((cl->cmd.flags & CMD_EXECFALSE && !WEXITSTATUS(status))
			|| (cl->cmd.flags & CMD_EXECTRUE && WEXITSTATUS(status)))
			return (EXS_NOEXEC);
	}
	return (EXS_SUCCESS);
}

void	execute_cmd(t_data *msh, t_command_lst *cl)
{
	if (do_redirection(&msh->exec, cl->cmd) == EXS_ERROR)
		return ;
	if ((cl->cmd.flags & CMD_PIPE || !(cl->cmd.flags & CMD_BUILTIN))
		&& !check_exec(&msh->exec, cl))
	{
		create_child(&msh->exec);
		if (!msh->exec.pid_curr)
		{
			if (dup2(msh->exec.infd, STDIN_FILENO) == -1
				|| dup2(msh->exec.outfd, STDOUT_FILENO) == -1)
				msh_error(ERDUP2);
			close_fds(&msh->exec, 1);
			if (cl->cmd.flags & CMD_SUBSHELL)
				execute_cmd_lst(msh, cl->cmd.elem.cmds);
			else
				msh->exec.status = execute_simple_cmd(msh, &msh->exec, cl);
			exit_prg(msh, msh->exec.status);
		}
	}
	else
		msh->exec.status = execute_simple_cmd(msh, &msh->exec, cl);
}

int	execute_cmd_lst(t_data *msh, t_command_lst *cl)
{
	int	status;

	cl = msh->parser.cmd_lst;
	if (pipe(msh->exec.pipefd) == -1)
		msh_error(ERPIPE);
	while (cl)
	{
		execute_cmd(msh, cl);
		cl = cl->next;
	}
	close_fds(&msh->exec, 1);
	waitpid(msh->exec.pid_last, &status, 0);
	msh->exec.status = WEXITSTATUS(status);
	while (--msh->exec.child_nb)
		wait(0);
	return (msh->exec.status);
}
