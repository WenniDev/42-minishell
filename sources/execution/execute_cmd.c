#include "minishell.h"

int	execute_cmd_lst(t_data *msh, t_command_lst *cl);

int	exit_prg(int status)
{
	exit(status);
}

int	execute_simple_cmd(t_data *msh, t_exec *e, t_command cmd)
{
	do_redirection(msh, cmd);
	expand_word_lst(msh, &cmd.elem.words);
	if (cmd.flags & CMD_BUILTIN)
		return (execute_builtin(msh, cmd));
	e->cmd_path = get_path(msh, cmd);
	e->argv = copy_word_list(cmd.elem.words);
	execve(e->cmd_path, e->argv, e->env);
	return (msh_error(EREXECVE));
}

void	execute_in_subshell(t_data *msh, t_command cmd)
{
	do_redirection(msh, cmd);
	close_fds(&msh->exec);
	execute_cmd_lst(msh, cmd.elem.cmds);
	exit_prg(msh->exec.status);
}

void	execute_cmd(t_data *msh, t_command cmd)
{
	int	do_fork;

	do_fork = (cmd.flags & CMD_PIPE || !(cmd.flags & CMD_BUILTIN));
	if (do_fork)
	{
		msh->exec.pid_curr = fork();
		if (msh->exec.pid_curr == -1)
			msh_error(ERFORK);
		if (!msh->exec.pid_curr)
		{
			if (cmd.flags & CMD_SUBSHELL)
				execute_in_subshell(msh, cmd);
			else
				msh->exec.status = execute_simple_cmd(msh, &msh->exec, cmd);
			exit_prg(msh->exec.status);
		}
		msh->exec.pid_last = msh->exec.pid_curr;
		msh->exec.to_wait++;
	}
	msh->exec.status = execute_simple_cmd(msh, &msh->exec, cmd);
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
