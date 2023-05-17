#include "minishell_execute.h"
#include "minishell_redirect.h"
#include "minishell_error.h"

void	create_child(t_exec *e)
{
	e->pid_curr = fork();
	if (e->pid_curr == -1)
		msh_error(ERFORK);
	if (e->pid_curr)
		e->pid_last = e->pid_curr;
	e->child_nb++;
}

void	wait_childs(t_exec *e)
{
	if (waitpid(e->pid_last, &e->status, 0) == -1)
		msh_error(ERWAITPID);
	e->status = WEXITSTATUS(e->status);
	while (--e->child_nb)
		if (wait(0) == -1)
			msh_error(ERWAIT);
}

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

void	do_ft(int ft, int *ft_data1, int ft_data2)
{
	if (ft == CLOSE)
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
