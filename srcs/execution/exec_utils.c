#include "minishell_execute.h"
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
