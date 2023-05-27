/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:58:25 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:58:26 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"

static int	check_syntax(t_parser *p, int tk, int tk_last);
static int	read_token(t_parser *p, char **line_ptr);
static int	get_token(t_parser *p, char c_char, char n_char, char **line_ptr);
int			read_token_word(t_parser *p, char **line_ptr);
int			is_redir(int tk);
int			is_connector(int tk);

int	next_token(t_parser *p, int tk)
{
	int	tk_n;
	int	tk_last;

	ft_memset(&p->word, 0, sizeof (t_word_d));
	tk_last = tk;
	if ((!tk_last || tk_last == NEWLINE) && !get_line(p))
		return (p->status = EOF);
	tk_n = read_token(p, &p->line_ptr);
	if (tk_n == TOKEN_ERROR || check_syntax(p, tk_n, tk_last) == EXS_ERROR)
		return (p->status = EXS_SYNTAX_ERROR, TOKEN_ERROR);
	if (tk_n == '\n' && !p->state && !is_connector(tk_last))
		p->state = PST_END;
	return (tk_n);
}

static int	read_token(t_parser *p, char **line_ptr)
{
	int		token;
	char	c_char;
	char	n_char;

	c_char = get_char(line_ptr);
	while (c_char == SPACE)
		c_char = get_char(line_ptr);
	if (!c_char || c_char == '\n')
		return ('\n');
	n_char = get_char(line_ptr);
	if (is_meta(c_char))
		token = get_token(p, c_char, n_char, line_ptr);
	else
	{
		unget_char(line_ptr);
		unget_char(line_ptr);
		token = read_token_word(p, line_ptr);
		if (token == WORD && !p->word.lval)
			return (malloc_error());
	}
	return (token);
}

static int	get_token(t_parser *p, char c_char, char n_char, char **line_ptr)
{
	if (c_char == n_char)
	{
		if (c_char == '<')
			return (LESS_LESS);
		if (c_char == '>')
			return (GREATER_GREATER);
		if (c_char == '|')
			return (OR_OR);
		if (c_char == '&')
			return (AND_AND);
	}
	unget_char(line_ptr);
	if (c_char == '(')
		p->state |= PST_SUBSHELL;
	if (c_char == ')' && --(p->pc) == 0)
		p->state &= ~PST_SUBSHELL;
	return ((int)c_char);
}

static int	check_syntax(t_parser *p, int tk, int tk_last)
{
	if (p->pc < 0)
		return (syntax_error(ERTOK, tk, p->word.lval));
	if (tk == '(')
		(p->pc)++;
	if ((!tk_last && is_connector(tk))
		|| (tk_last == WORD && tk == '(')
		|| (is_connector(tk_last) && is_connector(tk))
		|| (is_redir(tk_last) && (is_connector(tk) || tk == '\n'))
		|| (tk_last == '(' && tk == ')')
		|| (tk_last == ')' && tk == WORD))
		return (syntax_error(ERTOK, tk, p->word.lval));
	return (EXIT_SUCCESS);
}
