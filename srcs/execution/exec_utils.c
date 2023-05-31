/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:42:48 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:42:49 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execute.h"
#include "minishell_redirect.h"
#include "minishell_error.h"

void	create_child(t_exec *e)
{
	e->pid_curr = fork();
	if (e->pid_curr == -1)
		msh_error(ERFORK);
	if (!e->pid_curr)
		e->child = true;
	if (e->pid_curr)
		e->pid_last = e->pid_curr;
	e->child_nb++;
}

void	wait_childs(t_exec *e)
{
	int	sig;

	sig = 0;
	if (waitpid(e->pid_last, &e->status, 0) == -1)
		msh_error(ERWAITPID);
	if (WIFSIGNALED(e->status))
		sig = WTERMSIG(e->status);
	if (sig == SIGINT)
		printf("\n");
	if (sig == SIGQUIT)
		printf("%s\n", QUITMSG);
	e->status = WEXITSTATUS(e->status);
	while (--e->child_nb)
		if (wait(0) == -1)
			msh_error(ERWAIT);
}

void	copy_word_list(t_command_lst *cl)
{
	t_word_lst	*elem;
	int			i;

	i = 0;
	elem = cl->cmd.elem.words;
	while (elem)
	{
		elem = elem->next;
		cl->cmd.argc++;
	}
	cl->cmd.argv = (char **)sfcalloc(cl->cmd.argc + 1, sizeof (char *));
	elem = cl->cmd.elem.words;
	while (elem)
	{
		cl->cmd.argv[i] = elem->word->lval;
		elem = elem->next;
		i++;
	}
}

void	do_ft(int ft, int *ft_data1, int ft_data2)
{
	if (ft == CLOSE && ft_data1)
	{
		if (*ft_data1 && close(*ft_data1) == -1)
			msh_error(ERCLOSE);
		*ft_data1 = 0;
	}
	if (ft == DUP)
	{
		*ft_data1 = dup(ft_data2);
		if (*ft_data1 == -1)
			msh_error(ERDUP);
	}
	if (ft == DUP2)
	{
		if (dup2(*ft_data1, ft_data2) == -1)
			msh_error(ERDUP2);
	}
	if (ft == PIPE)
	{
		if (pipe(ft_data1) == -1)
			msh_error(ERPIPE);
	}
}

int	is_reg_file(char *file)
{
	struct stat	infos;

	if (stat(file, &infos) == -1)
		return (0);
	if (!S_ISREG(infos.st_mode))
	{
		if (S_ISDIR(infos.st_mode))
			errno = EISDIR;
		else
			errno = EACCES;
		return (0);
	}
	return (1);
}
