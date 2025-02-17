/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:51:30 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 13:01:11 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"

void	add_simple_cmd(t_parser *p, int sep)
{
	t_command_lst	*new_cmd;

	new_cmd = (t_command_lst *)sfcalloc(1, sizeof (t_command_lst));
	new_cmd->cmd.flags |= CMD_SIMPLE;
	if (sep == '|')
	{
		if (!(p->cl_curr->cmd.flags & CMD_PIPE))
			p->cl_curr->cmd.flags |= (CMD_PIPE | CMD_STARTPIPE);
		p->cl_curr->cmd.flags &= ~CMD_ENDPIPE;
		new_cmd->cmd.flags |= (CMD_PIPE | CMD_ENDPIPE);
	}
	else if (sep == OR_OR)
		new_cmd->cmd.flags |= CMD_EXECFALSE;
	else if (sep == AND_AND)
		new_cmd->cmd.flags |= CMD_EXECTRUE;
	if (p->cmd_lst)
	{
		p->cl_curr->next = new_cmd;
		new_cmd->prev = p->cl_curr;
	}
	else
		p->cmd_lst = new_cmd;
	p->cl_curr = new_cmd;
}

void	add_word(t_parser *p, t_word_d wd)
{
	t_word_lst	*wl;
	t_word_lst	*new_wl;
	t_word_d	*new_wd;

	new_wl = (t_word_lst *)sfcalloc(1, sizeof (t_word_lst));
	new_wd = (t_word_d *)sfcalloc(1, sizeof (t_word_d));
	*new_wd = wd;
	new_wl->word = new_wd;
	wl = p->cl_curr->cmd.elem.words;
	if (wl)
	{
		while (wl->next)
			wl = wl->next;
		wl->next = new_wl;
	}
	else
	{
		p->cl_curr->cmd.elem.words = new_wl;
		if (ft_is_builtin(new_wl->word->lval))
			p->cl_curr->cmd.flags |= CMD_BUILTIN;
	}
}

void	add_red(t_parser *p, t_word_d wd, int flags)
{
	t_red		*red;
	t_red		*new_red;
	t_word_d	*new_wd;

	new_red = (t_red *)sfcalloc(1, sizeof (t_red));
	new_wd = (t_word_d *)sfcalloc(1, sizeof (t_word_d));
	*new_wd = wd;
	new_red->filename = new_wd;
	new_red->rflags = flags;
	if (flags & RED_IN)
		new_red->oflags = O_RDONLY;
	if (flags & (RED_TRUNC))
		new_red->oflags = O_CREAT | O_WRONLY | O_TRUNC;
	if (flags & (RED_APPEND))
		new_red->oflags = O_CREAT | O_WRONLY | O_APPEND;
	red = p->cl_curr->cmd.reds;
	if (red)
	{
		while (red->next)
			red = red->next;
		red->next = new_red;
	}
	else
		p->cl_curr->cmd.reds = new_red;
}

void	add_heredoc(t_parser *p, t_red *r)
{
	t_hd	*new;
	t_hd	*hd_red;

	if (++p->hd_nb > HEREDOC_MAX)
		msh_error(ERHDMAX);
	new = (t_hd *)sfcalloc(1, sizeof (t_hd));
	new->red = r;
	new->red->heredoc_eof = r->filename->lval;
	hd_red = p->hd_lst;
	if (!p->hd_lst)
		p->hd_lst = new;
	else
	{
		while (hd_red->next)
			hd_red = hd_red->next;
		hd_red->next = new;
	}
}

/*
 * TODO: leak when ((ls))
 */

void	add_subshell_cmd(t_parser *p, t_command_lst *cl_curr)
{
	t_command_lst	*new_cmd;
	t_addr_lst		*new_sub;

	new_cmd = (t_command_lst *)sfcalloc(1, sizeof (t_command_lst));
	new_sub = (t_addr_lst *)sfcalloc(1, sizeof (t_addr_lst));
	new_cmd->cmd.flags |= CMD_SUBSHELL;
	new_cmd->prev = cl_curr->prev;
	if (cl_curr->prev)
		cl_curr->prev->next = new_cmd;
	else if (p->cmd_lst == cl_curr)
		p->cmd_lst = new_cmd;
	else
		p->sub_lst->addr->cmd.elem.cmds = new_cmd;
	cl_curr->prev = NULL;
	new_cmd->cmd.elem.cmds = cl_curr;
	new_sub->addr = new_cmd;
	if (!p->sub_lst)
		p->sub_lst = new_sub;
	else
	{
		new_sub->prev = p->sub_lst;
		p->sub_lst = new_sub;
	}
}
