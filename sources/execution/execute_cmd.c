#include "minishell.h"

int	execute_cmd_lst(t_data *msh, t_command_lst *cl);

static const t_builtin	g_builtin[] ={
		{"env", b_env},
		{"pwd", b_pwd},
		{"export", b_export},
		{"unset", b_unset},
		{"echo", b_echo},
		{"exit", b_exit}
};

int	exit_prg(int status)
{
	exit(status);
}

int	execute_builtin(t_data *msh, t_exec *e, t_command cmd)
{
	int			i;
	int			argc;
	int			status;
	t_word_lst	*elem;

	i = 0;
	close_fds(e, 0);
	expand_word_lst(msh, &cmd.elem.words);
	if (!cmd.elem.words->word->lval)
		return (EXIT_SUCCESS);
	elem = cmd.elem.words;
	while (elem && argc++)
		elem = elem->next;
	e->argv = copy_word_lst(cmd.elem.words);
	while (ft_strcmp(e->argv[0], g_builtin[i].cmd))
		i++;
	status = g_builtin[i].ft(e, argc, e->argv);
	clean_argv(e, e->argv);
	return (status);
}

void	execute_simple_cmd(t_data *msh, t_exec *e, t_command cmd)
{
	int	last_status;

	if (cmd.flags & CMD_EXECTRUE || cmd.flags & CMD_EXECFALSE)
	{
		if (waitpid(e->pid_last, &last_status, 0) == -1)
			msh_error(ERWAITPID);
		if ((cmd.flags & CMD_EXECFALSE && !WEXITSTATUS(last_status))
			|| (cmd.flags & CMD_EXECTRUE && WEXITSTATUS(last_status)))
			exit_prg(e->status);
	}
	expand_word_lst(msh, &cmd.elem.words);
	e->cmd_path = get_path(msh, cmd);
	e->argv = copy_word_list(cmd.elem.words);
	execve(e->cmd_path, e->argv, e->env);
	msh_error(EREXECVE);
}

void	execute_cmd(t_data *msh, t_command cmd)
{
	do_redirection(msh, cmd);
	if (cmd.flags & CMD_PIPE || !(cmd.flags & CMD_BUILTIN))
	{
		msh->exec.pid_curr = fork();
		if (msh->exec.pid_curr == -1)
			msh_error(ERFORK);
		if (!msh->exec.pid_curr)
		{
			if (dup2(msh->exec.infd, STDIN_FILENO) == -1
				|| dup2(msh->exec.outfd, STDOUT_FILENO) == -1)
				msh_error(ERDUP2);
			close_fds(&msh->exec, 1);
			if (cmd.flags & CMD_SUBSHELL)
				execute_cmd_lst(msh, cmd.elem.cmds);
			else if (cmd.flags & CMD_SIMPLE)
				execute_simple_cmd(msh, &msh->exec, cmd);
			else if (cmd.flags & CMD_BUILTIN)
				msh->exec.status = execute_builtin(msh, &msh->exec, cmd);
			exit_prg(msh->exec.status);
		}
		msh->exec.pid_last = msh->exec.pid_curr;
		msh->exec.to_wait++;
	}
	msh->exec.status = execute_builtin(msh, &msh->exec, cmd);
}

int	execute_cmd_lst(t_data *msh, t_command_lst *cl)
{
	cl = msh->parser.cmd_lst;
	if (pipe(msh->exec.pipefd) == -1)
		msh_error(ERPIPE);
	while (cl)
	{
		execute_cmd(msh, cl->cmd);
		cl = cl->next;
	}
	return (msh->exec.status);
}
