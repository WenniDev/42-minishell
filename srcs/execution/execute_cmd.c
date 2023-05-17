#include "minishell.h"
#include "minishell_builtins.h"

int		exec_cmd_lst(t_data *msh, t_exec *e, t_command_lst *cl);
char	*get_path(t_data *msh, char *cmd_name);
void	clean_argv(char **argv);

static const t_builtin	g_builtin[] ={
		{"env", b_env}/*, {"pwd", b_pwd}, {"export", b_export},*/
/*		{"unset", b_unset}, {"echo", b_echo}, {"exit", b_exit}*/
};

int	execute_builtin(t_exec *e, t_command cmd)
{
	int			i;
	int			status;

	i = 0;
	while (ft_strcmp(cmd.argv[0], g_builtin[i].cmd))
		i++;
	status = g_builtin[i].ft(e, cmd.argc, cmd.argv);
	clean_argv(cmd.argv);
	return (status);
}

int	execute_simple_cmd(t_data *msh, t_exec *e, t_command cmd)
{
/*	expand_word_lst(msh, &cl->cmd.elem.words);*/
	if (!cmd.elem.words->word->lval)
		return (EXIT_SUCCESS);
	cmd.argv = copy_word_list(cmd.elem.words);
	if (cmd.flags & CMD_BUILTIN)
		return (execute_builtin(e, cmd));
	cmd.cmd_path = get_path(msh, cmd.elem.words->word->lval);
	execve(cmd.cmd_path, cmd.argv, e->env);
	msh_error(EREXECVE);
	return (EXIT_FAILURE);
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

void	exec_cmd(t_data *msh, t_exec *e, t_command cmd)
{
	if (cmd.flags & CMD_PIPE || !(cmd.flags & CMD_BUILTIN))
	{
		create_child(e);
		if (!msh->exec.pid_curr)
		{
			e->child_nb = 0;
			close_all(e);
			if (cmd.flags & CMD_SUBSHELL)
				exec_cmd_lst(msh, e, cmd.elem.cmds);
			else
				e->status = execute_simple_cmd(msh, e, cmd);
			exit_prg(msh, e->status);
		}
	}
	else
		 e->status = execute_simple_cmd(msh, e, cmd);
}

int    exec_cmd_lst(t_data *msh, t_exec *e, t_command_lst *cl)
{
	set_fds(e, 0);
	while (cl)
	{
		if (check_exec(cl->cmd.flags, e->pid_last) || do_redir(e, cl->cmd))
		{
			cl = cl->next;
			continue ;
		}
		exec_cmd(msh, e, cl->cmd);
		cl = cl->next;
	}
	set_fds(e, 1);
	if (e->child_nb)
		wait_childs(e);
	return (e->status);
}
