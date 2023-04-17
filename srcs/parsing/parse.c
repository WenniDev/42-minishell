//	NORM
//		-missing header

#include "spash.h"
#include "spash_parsing.h"
#include "spash_error.h"
#include "libft.h"

char	**create_grammar(t_data *data)
{
	char	**grammar;

	grammar = (char **)ft_calloc(11, sizeof (char *));
	if (!grammar)
		(sperr(data, MFAIL, "create_grammar", 2), exit_prg(data));
	grammar[0] = MUCH_LESS;
	grammar[1] = MUCH_GREATER;
	grammar[2] = DOUBLE_AMPERSAND;
	grammar[3] = DOUBLE_VERTICAL_BAR;
	grammar[4] = LESS;
	grammar[5] = GREATER;
	grammar[6] = VERTICAL_BAR;
	grammar[7] = OPENED_PARENTHESIS;
	grammar[8] = CLOSED_PARENTHESIS;
	grammar[9] = S_NEWLINE;
	return (grammar);
}

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
			quote = ptr[i];
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
 * @param token current token
 * @param ptr a pointer to the current location on command line
 * @param grammar a string table containing the predefined grammar
 */
void fill_token_data(t_data *data, t_token *token, char *ptr, char **grammar)
{
	t_op	op;

	op = 0;
	if (!*ptr)
		op = NEWLINE;
	while (*ptr && op != NONE)
	{
		if (!ft_strncmp(ptr, grammar[op], ft_strlen(grammar[op])))
			break;
		op++;
	}
	token->value.op = op;
	if (op == HEREDOC_RED || op == IN_RED || op == OUTAP_RED || op == OUTTR_RED)
		token->type = RED_OP;
	else if (op != NONE)
		token->type = CTRL_OP;
	else
	{
		token->type = WORD;
		token->value.word = get_word_value(data, ptr);
	}
}

/**
 * @brief Malloc a token struct and fills it with the next tokens data from
 * command line
 * @param data the main data struct
 * @param grammar a string table containig the predifined grammar
 * @return a pointer to the token struct
 */
t_token	*create_token(t_data *data, char **grammar)
{
	t_token		*token;
	static char *ptr;

	if (!ptr)
		ptr = data->c_line;
	token = (t_token *)ft_calloc(1, sizeof (t_token));
	if (!token)
	{
		sperr(data, MFAIL, "create token", 2);
		exit_prg(data);
	}
	fill_token_data(data, token, ptr, grammar);
	if (token->type == WORD)
		ptr += ft_strlen(token->value.word);
	else if (token->value.op == NEWLINE)
		ptr++;
	else
		ptr += ft_strlen(grammar[token->value.op]);
	return (token);
}

/**
 * @brief Parse the command line into an command table
 * @param data the main data struct
 */
void	parse(t_data *data)
{
	t_token	*token;
	char 	**grammar;
	int		syntax_status;

	grammar = create_grammar(data);
	while (data && data->c_line)
	{
		token = create_token(data, grammar);
		syntax_status = check_syntax(data, token, grammar);
		if (syntax_status == FALSE || syntax_status == END)
		{
			free(token);
			break;
		}
		else if (syntax_status == NO_END)
		{
			get_cmd_line(data);
			continue ;
		}
//		parse_token(data, token);
	}
	free(grammar);
	if (data->error.num)
		put_sperr(data->error);
}