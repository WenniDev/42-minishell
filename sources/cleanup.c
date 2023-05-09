#include "minishell.h"

void	clean_elems(t_word_lst *words, t_red *reds)
{
	void	*tmp;

	while (words)
	{
		tmp = words->next;
		free(words->word_d->lval);
		free(words->word_d);
		free(words);
		words = (t_word_lst *)tmp;
	}
	while (reds)
	{
		tmp = reds->next;
		free(reds->filename->lval);
		free(reds->filename);
		free(reds);
		reds = tmp;
	}
}

void	clean_cmd(t_command_lst *cl)
{
	void	*tmp;

	if (cl->cmd.type == simple_cmd)
		clean_elems(cl->cmd.elems.words, cl->cmd.reds);
	else if (cl->cmd.type == subshell_cmd)
	{
		clean_elems(NULL, cl->cmd.reds);
		while (cl->cmd.elems.cmds)
		{
			tmp = cl->cmd.elems.cmds->next;
			clean_cmd(cl->cmd.elems.cmds);
			free(cl->cmd.elems.cmds);
			cl->cmd.elems.cmds = (t_command_lst *)tmp;
		}
	}
}
