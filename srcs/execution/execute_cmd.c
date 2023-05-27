/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:15:39 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/21 17:27:01 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_builtins.h"
#include "minishell_expand.h"

int		exec_cmd_lst(t_data *msh, t_exec *e, t_command_lst *cl);
char	*get_path(t_data *msh, char *cmd_name);

static const t_builtin	g_builtin[7] ={
		{"env", b_env}, {"pwd", b_pwd}, {"cd", b_cd}, {"export", b_export},
		{"unset", b_unset}, {"echo", b_echo}, {"exit", b_exit}
};

int	execute_builtin(t_data *msh, t_command cmd)
{
	int			i;
	int			status;

	i = 0;
	while (ft_strcmp(cmd.argv[0], g_builtin[i].cmd))
		i++;
	status = g_builtin[i].ft(msh, cmd.argc, cmd.argv);
	return (status);
}

int	execute_simple_cmd(t_data *msh, t_exec *e, t_command_lst *cl)
{
	if (!cl->cmd.elem.words || !(*cl->cmd.elem.words->word->lval))
		return (EXIT_SUCCESS);
	copy_word_list(cl);
	if (cl->cmd.flags & CMD_BUILTIN)
		return (execute_builtin(msh, cl->cmd));
	cl->cmd.cmd_path = get_path(msh, cl->cmd.elem.words->word->lval);
	execve(cl->cmd.cmd_path, cl->cmd.argv, e->env);
	msh_error(EREXECVE);
	return (EXIT_FAILURE);
}

int	check_exec(t_exec *e, int f)
{
	int	status;

	if (e->child_nb && f & (CMD_EXECTRUE | CMD_EXECFALSE))
	{
		if (waitpid(e->pid_last, &status, 0) == -1)
			msh_error(ERWAITPID);
		e->child_nb--;
		e->status = WEXITSTATUS(status);
		if ((f & CMD_EXECFALSE && !WEXITSTATUS(status))
			|| (f & CMD_EXECTRUE && WEXITSTATUS(status)))
			return (EXS_NOEXEC);
	}
	else if ((f & (CMD_EXECTRUE | CMD_EXECFALSE)))
	{
		if ((f & CMD_EXECTRUE && e->status)
			|| ( f & CMD_EXECFALSE && !e->status))
			return (EXS_NOEXEC);
	}
	return (EXS_SUCCESS);
}

void	exec_cmd(t_data *msh, t_exec *e, t_command_lst *cl)
{
	if (!(cl->cmd.flags & CMD_SUBSHELL))
	{
		expand(e->status, &cl->cmd.elem.words);
		if (ft_is_builtin(cl->cmd.elem.words->word->lval))
			cl->cmd.flags |= CMD_BUILTIN;
	}
	if (cl->cmd.flags & CMD_PIPE || !(cl->cmd.flags & CMD_BUILTIN))
	{
		create_child(e);
		if (!msh->exec.pid_curr)
		{
			e->child_nb = 0;
			close_all(e);
			if (cl->cmd.flags & CMD_SUBSHELL)
				exec_cmd_lst(msh, e, cl->cmd.elem.cmds);
			else
				e->status = execute_simple_cmd(msh, e, cl);
			exit_prg(msh, e->status);
		}
	}
	else
		 e->status = execute_simple_cmd(msh, e, cl);
}

int    exec_cmd_lst(t_data *msh, t_exec *e, t_command_lst *cl)
{
	set_fds(e, 0);
	e->status = msh->status;
	while (cl)
	{
		if (check_exec(e, cl->cmd.flags) || do_redir(e->status, e, cl->cmd))
		{
			cl = cl->next;
			set_fds(e, 2);
			continue ;
		}
		exec_cmd(msh, e, cl);
		cl = cl->next;
	}
	set_fds(e, 1);
	if (e->child_nb)
		wait_childs(e);
	return (e->status);
}
