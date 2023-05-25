/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:42:49 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/23 18:42:49 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_free((void **)&words->word->lval);
		ft_free((void **)&words->word);
		ft_free((void **)&words);
		words = (t_word_lst *)tmp;
	}
	while (reds)
	{
		tmp = reds->next;
		ft_free((void **)&reds->filename->lval);
		ft_free((void **)&reds->hd_content);
		ft_free((void **)&reds->filename);
		ft_free((void **)&reds);
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
			ft_free((void **)&cl->cmd.elem.cmds);
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
	ft_free((void **)&msh);
}
