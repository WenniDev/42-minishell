//	NORM
//		-missing header
//	TODO
//		-rewrite token_error

#include "spash_types.h"
#include "spash_parsing.h"
#include "spash_error.h"
#include <stdbool.h>

int	token_error(t_token *tk, t_token *prev, int pc)
{
	if (pc < 0)
		return (true);
	if (tk->type == CTRL_OP)
	{
		if ((!prev && tk->op != O_PAR && tk->op != NEWLINE)
			|| (prev && prev->type == RED_OP)
			|| (prev && prev->type == WORD && tk->op == O_PAR)
			|| (prev && prev->type == CTRL_OP && tk->op != O_PAR && tk->op != NEWLINE))
			return (true);
	}
	else if (tk->type == RED_OP)
	{
		if (prev && prev->type == RED_OP)
			return (true);
	}
	else
	{
		if (prev && prev->type == CTRL_OP && prev->op == C_PAR)
			return (true);
	}
	return (false);
}

/**
 * @brief Check syntax error and end using the previously parsed token
 * @param data the main data struct
 * @param tk current token
 * @return the syntaxt status
 */
int	check_syntax(t_data *data, t_token *tk)
{
	static int	pc;

	if (tk->op == O_PAR)
		pc++;
	else if (tk->op == C_PAR)
		pc--;
	if (token_error(tk, tk->prev, pc))
		return (pc = 0, sperr(data, UNTOK, tk->value, 2), ERROR);
	else if (tk->op == NEWLINE && pc > 0)
		return (NO_END);
	else if (tk->op == NEWLINE)
		return (END);
	return (CORRECT);
}