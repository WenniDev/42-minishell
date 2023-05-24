#include "minishell_parse.h"

void	parser_act(t_parser *p, int act);
void	add_word(t_parser *p, t_word_d wd);
void	add_subshell_cmd(t_parser *p, t_command_lst *cmd_curr);
void	add_red(t_parser *p, t_word_d wd, int flags);
void	add_heredoc(t_parser *p, t_red *r);
void	add_simple_cmd(t_parser *p, int sep);
int		tk_symbol(int tk);

static const char		*g_symbol_name[] = {
	"invalid token", "<", ">", "<<", ">>", "|", "||", "&&", "(", ")", "newline",
	"word", "simple_cmd", "subshell_cmd"
};

static const u_int8_t	g_symbol_num[] = {
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	10,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	8,	9,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	1,	0,	2,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	5,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	3,	4,	7,	6,
	11
};

static const u_int8_t	g_act_table[] = {
	0,	0,	0,	0,	0,	7,	8,	9,	10,	11,
	0,	1,	2,	3,	4,	5,	0,	0,	0,	0,
};

int	parse(t_parser *p)
{
	while (p->state != PST_END)
	{
		if (!p->cmd_lst)
			parser_act(p, 6);
		p->tk = next_token(p, p->tk);
		if (p->tk < 0)
			break ;
		p->ssymc += tk_symbol(p->tk);
		p->act = g_act_table[p->ssymc];
		if (p->act)
		{
			parser_act(p, p->act);
			p->ssymc = 0;
		}
	}
	if (p->tk == EOF)
		p->eof = true;
	return (p->status);
}

void	parser_act(t_parser *p, int act)
{
	if (act == 1)
		add_word(p, p->word);
	else if (act == 2)
		add_red(p, p->word, RED_IN);
	else if (act == 3)
		add_red(p, p->word, RED_OUT | RED_TRUNC);
	else if (act == 4)
	{
		add_red(p, p->word, RED_IN | RED_HEREDOC);
		add_heredoc(p, ft_last_red(p->cl_curr->cmd.reds));
	}
	else if (act == 5)
		add_red(p, p->word, RED_OUT | RED_APPEND);
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

void	reset_parser(t_parser *p)
{
	void	*tmp;
	int		line;

	line = p->line;
	if (p->cmd_line)
		add_history(p->cmd_line);
	ft_free((void **)&p->cmd_line);
	ft_free((void **)&p->line_read);
	while (p->cmd_lst)
	{
		tmp = p->cmd_lst->next;
		clean_cmd(p->cmd_lst);
		ft_free((void **)&p->cmd_lst);
		p->cmd_lst = (t_command_lst *)tmp;
	}
	while (p->hd_lst)
	{
		tmp = p->hd_lst->next;
		ft_free((void **)&p->hd_lst->heredoc_eof);
		ft_free((void **)&p->hd_lst);
		p->hd_lst = (t_red *)tmp;
	}
	ft_memset(p, 0, sizeof (t_parser));
	p->line = line;
}

int	tk_symbol(int tk)
{
	return ((int)g_symbol_num[tk]);
}

const char	*tk_translate(int tk)
{
	return (g_symbol_name[tk_symbol(tk)]);
}
