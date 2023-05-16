/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:26:40 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/16 11:58:38 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"

void			add_word(t_parser *p, t_word_d wd);
void			add_subshell_cmd(t_parser *p, t_command_lst *cmd_curr);
void			add_red(t_parser *p, int src, t_word_d wd, int flags);
void			add_simple_cmd(t_parser *p, int sep);

void	parser_act(t_parser *p, int act)
{
	if (act == 1)
		add_word(p, p->word);
	else if (act == 2)
		add_red(p, 0, p->word, r_input);
	else if (act == 3)
		add_red(p, 1, p->word, r_output_tr);
	else if (act == 4)
		add_red(p, 0, p->word, r_heredoc);
	else if (act == 5)
		add_red(p, 1, p->word, r_output_ap);
	else if (act == 6)
		add_simple_cmd(p, 0);
	else if (act == 7)
		add_simple_cmd(p, '|');
	else if (act == 8)
		add_simple_cmd(p, OR_OR);
	else if (act == 9)
		add_simple_cmd(p, AND_AND);
	else if (act == 10)
		add_subshell_cmd(p, p->cl_curr);
	else if (act == 11)
		p->cl_curr = p->cl_last;
}

void	add_simple_cmd(t_parser *p, int sep)
{
	t_command_lst	*new_cmd;

	new_cmd = (t_command_lst *)sfcalloc(1, sizeof (t_command_lst));
	new_cmd->cmd.type = simple_cmd;
	if (sep == '|')
	{
		if (!(p->cl_curr->cmd.flags & CMD_PIPE))
			p->cl_curr->cmd.flags |= CMD_STARTPIPE;
		p->cl_curr->cmd.flags &= ~CMD_ENDPIPE;
		new_cmd->cmd.flags |= CMD_PIPE;
		new_cmd->cmd.flags |= CMD_ENDPIPE;
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
		if (ft_strstr(BUILTINS, new_wl->word->lval))
			p->cl_curr->cmd.flags |= CMD_BUILTIN;
	}
}

void	add_red(t_parser *p, int src, t_word_d wd, int flags)
{
	t_red		*red;
	t_red		*new_red;
	t_word_d	*new_wd;

	new_red = (t_red *)sfcalloc(1, sizeof (t_red));
	new_wd = (t_word_d *)sfcalloc(1, sizeof (t_word_d));
	*new_wd = wd;
	new_red->filename = new_wd;
	new_red->rflags = src;
	if (flags == r_input)
		new_red->oflags = O_RDONLY;
	if (flags == r_output_tr)
		new_red->oflags = O_CREAT | O_WRONLY | O_TRUNC;
	if (flags == r_output_ap)
		new_red->oflags = O_CREAT | O_WRONLY | O_APPEND;
/*	if (flags == r_heredoc)
		add_heredoc(p, new_red);*/
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

void	add_subshell_cmd(t_parser *p, t_command_lst *cmd_curr)
{
	t_command_lst	*new_cmd;

	new_cmd = (t_command_lst *)sfcalloc(1, sizeof (t_command_lst));
	new_cmd->cmd.type = subshell_cmd;
	new_cmd->cmd.flags |= CMD_SUBSHELL;
	new_cmd->prev = cmd_curr->prev;
	if (cmd_curr->prev)
		cmd_curr->prev->next = new_cmd;
	else
		p->cmd_lst = new_cmd;
	cmd_curr->prev = NULL;
	new_cmd->cmd.elem.cmds = cmd_curr;
	p->cl_last = new_cmd;
}
