//	NORM
//		-missing header

#include "spash_types.h"
#include "spash_parsing.h"
#include "spash_error.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int	token_error(t_token *token, t_token *prev, int pc)
{
	if (!token || pc < 0)
		return (true);
	if (token->type == CTRL_OP)
	{
		if ((!prev && token->value.op != O_PAR && token->value.op != NEWLINE)
			|| (prev && prev->type == RED_OP)
			|| (prev && prev->type == WORD && token->value.op == O_PAR)
			|| (prev && prev->type == CTRL_OP && token->value.op != O_PAR))
			return (true);
	}
	if (prev && token->type == RED_OP && prev->type == RED_OP)
		return (true);
	return (false);
}

/**
 * @brief Check syntax error and end using the previously parsed token
 * @param data the main data struct
 * @param token current token
 * @param grammar a string table containig the predefined grammar
 * @return the syntaxt status
 */
int	check_syntax(t_data *data, t_token *token, char **grammar)
{
	static t_token	*prev;
	static int		pc;

	if (token->type == CTRL_OP && token->value.op == O_PAR)
		pc++;
	else if (token->type == CTRL_OP && token->value.op == C_PAR)
		pc--;
	if (token_error(token, prev, pc))
		return (pc = 0, sperr(data, UNTOK, grammar[token->value.op], 2), FALSE);
	if (prev)
		free(prev);
	if (token->type == CTRL_OP && token->value.op == NEWLINE && pc > 0)
		return (NO_END);
	else if (token->type == CTRL_OP && token->value.op == NEWLINE)
		return (END);
	prev = token;
	return (CORRECT);
}