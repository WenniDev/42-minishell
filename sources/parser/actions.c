#include "minishell_parse.h"

void	add_simple_cmd(t_parser *p, int sep)
{
	t_command_lst	*new_cmd;

	new_cmd = (t_command_lst *)sfcalloc(1, sizeof (t_command_lst));
	new_cmd->cmd.flags |= CMD_SIMPLE;
	if (sep == '|')
	{
		if (!(p->cl_curr->cmd.flags & CMD_PIPE))
			p->cl_curr->cmd.flags |= (CMD_STARTPIPE | CMD_PIPE);
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
		if (ft_strstr(BUILTINS, new_wl->word->lval))
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
	if (flags & (RED_OUT | RED_TRUNC))
		new_red->oflags = O_CREAT | O_WRONLY | O_TRUNC;
	if (flags & (RED_OUT | RED_APPEND))
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
	t_red	*new;
	t_red	*hd_red;

	new = (t_red *)sfcalloc(1, sizeof (t_red));
	new = r;
	new->heredoc_eof = new->filename->lval;
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

void	add_subshell_cmd(t_parser *p, t_command_lst *cmd_curr)
{
	t_command_lst	*new_cmd;

	new_cmd = (t_command_lst *)sfcalloc(1, sizeof (t_command_lst));
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
