#include "minishell.h"

void	clean_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		ft_free((void **)&argv[i]);
		i++;
	}
	ft_free((void **)&argv);
}

void	clean_elems(t_word_lst *words, t_red *reds)
{
	void	*tmp;

	while (words)
	{
		tmp = words->next;
		free(words->word->lval);
		free(words->word);
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

	if (cl->cmd.flags & CMD_SIMPLE)
	{
		ft_free((void **)&cl->cmd.cmd_path);
		clean_elems(cl->cmd.elem.words, cl->cmd.reds);
		ft_free((void **)&cl->cmd.argv);
	}
	else if (cl->cmd.flags & CMD_SUBSHELL)
	{
		clean_elems(NULL, cl->cmd.reds);
		while (cl->cmd.elem.cmds)
		{
			tmp = cl->cmd.elem.cmds->next;
			clean_cmd(cl->cmd.elem.cmds);
			free(cl->cmd.elem.cmds);
			cl->cmd.elem.cmds = (t_command_lst *)tmp;
		}
	}
}

void	clean_all(t_data *msh)
{
	if (!msh)
		return ;
	reset_parser(&msh->parser);
	close_all(&msh->exec);
	ft_free((void **)&msh->exec.pipefd);
	clean_argv(msh->exec.env);
	free(msh);
}
