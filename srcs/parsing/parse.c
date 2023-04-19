//	NORM
//		-missing header

#include "spash.h"
#include "spash_parsing.h"
#include "spash_error.h"
#include "libft.h"

/**
 * @brief Get the words value while respecting quoting rules.
 * @param data the main data stuct
 * @param ptr a pointer to the begining of the word
 * @return the words value or NULL if a quote was unclosed (updating error)
 */
char	*get_word_value(t_data *data, char *ptr)
{
	char	*value;
	char	quote;
	int		i;

	i = 0;
	while (ptr && ptr[i] && !ft_strchr(METACHARACTERS, ptr[i]))
	{
		if (ptr[i] == SINGLE_QUOTE || ptr[i] == DOUBLE_QUOTE)
		{
			quote = ptr[i++];
			while (ptr[i] && ptr[i] != quote)
				i++;
			if (!ptr[i])
				return (uncquote_error(data, quote), NULL);
		}
		i++;
	}
	value = ft_substr(ptr, 0, i);
	if (!value)
		(sperr(data, MFAIL, "get_word_value", 2), exit_prg(data));
	return (value);
}

/**
 * @brief Get the tokens data from the command line
 * @param data the main data struct
 * @param tk current token
 * @param grammar a string table containing the predefined grammar
 * @param ptr a pointer to the current location on command line
 */
void token_data(t_data *data, t_token *tk, char **grammar, char *ptr)
{
	if (!*ptr)
		tk->op = NEWLINE;
	while (*ptr && tk->op != NONE)
	{
		tk->value = grammar[tk->op];
		if (!ft_strncmp(ptr, tk->value, ft_strlen(tk->value)))
			break;
		tk->op++;
	}
	if (tk->op == IN_RED || tk->op == HEREDOC_RED || tk->op == OUTTR_RED
		|| tk->op == OUTAP_RED)
		tk->type = RED_OP;
	else if (tk->op != NONE)
		tk->type = CTRL_OP;
	else
		tk->type = WORD;
	if (tk->op == NEWLINE)
		tk->value = S_NEWLINE;
	else if (tk->op == NONE)
		tk->value = get_word_value(data, ptr);
}

t_token	*new_token(t_data *data, t_syntax *stx, char **ptr)
{
	t_token		*tk_new;

	tk_new = (t_token *)ft_calloc(1, sizeof (t_token));
	if (!tk_new)
		(sperr(data, MFAIL, "create tk_new", 2), exit_prg(data));
	if (stx->tk)
		tk_new->prev = stx->tk;
	while (**ptr == SPACE)
		(*ptr)++;
	token_data(data, tk_new, stx->grammar, *ptr);
	*ptr += ft_strlen(tk_new->value);
	return (tk_new);
}

/**
 * @brief Parse the command line into an command table
 * @param data the main data struct
 */
void	parse(t_data *data)
{
	char		*ptr;

	ptr = data->c_line;
	while (ptr && data->stx.stat != END)
	{
		data->stx.tk = new_token(data, &data->stx, &ptr);
		data->stx.stat = check_syntax(data, data->stx.tk);
		if (!data->stx.tk->value || data->stx.stat == FALSE)
			break ;
		else if (data->stx.stat == NO_END)
			ptr = get_cmd_line(data);
//		parse_token(data, data->stx.tk);
	}
	if (data->error.num)
		put_sperr(data->error);
}