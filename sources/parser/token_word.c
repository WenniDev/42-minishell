#include "minishell_parse.h"

static int	read_quotes(t_parser *p, char quote, char **line_ptr);

static int	read_token_word(t_parser *p, char **line_ptr)
{
	char 		c;
	char		quote;
	char 		*word_start;

	word_start = *line_ptr;
	c = get_char(line_ptr);
	while (c && !is_meta(c))
	{
		if (c == '~')
			p->word.flags |= W_TILDE;
		if (c == '$')
			p->word.flags |= W_DOLLAR;
		if ((c == '\'' || c == '"') && read_quotes(p, c, line_ptr))
			return (syntax_error(NULL, quote, NULL));
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
