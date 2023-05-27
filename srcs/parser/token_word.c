/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:13:18 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/27 10:58:18 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"

static int	read_quotes(t_parser *p, char quote, char **line_ptr);

int	read_token_word(t_parser *p, char **line_ptr)
{
	char	c;
	char	*word_start;

	word_start = *line_ptr;
	c = get_char(line_ptr);
	while (c && !is_meta(c))
	{
		if (c == '$')
			p->word.flags |= W_DOLLAR;
		if ((c == '\'' || c == '"') && read_quotes(p, c, line_ptr))
			return (syntax_error(NULL, c, NULL));
		c = get_char(line_ptr);
	}
	unget_char(line_ptr);
	p->word.lval = ft_substr(word_start, 0, *line_ptr - word_start);
	return (WORD);
}

static int	read_quotes(t_parser *p, char quote, char **line_ptr)
{
	char	c;

	p->word.flags |= W_QUOTES;
	c = get_char(line_ptr);
	while (c && c != quote)
	{
		if (c == '$')
			p->word.flags |= W_DOLLAR;
		c = get_char(line_ptr);
	}
	if (!c)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
