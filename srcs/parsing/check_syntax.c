//	NORM
//		-missing header

#include "spash_parsing.h"
#include "spash_error.h"
#include <stdbool.h>
#include "libft.h"

char	*get_fbd_values(t_token *prev)
{
	if (!prev)
		return ("| || &&");
	if (prev->type == RED_OP)
		return ("newline | || && < << > >> ( )");
	if (prev->op == C_PAR || prev->op == NEWLINE)
		return ("(");
	if (prev->type == CTRL_OP)
		return ("| || && )");
	else
		return (NULL);
}

int	token_error(t_data *data, t_token *tk, int pc)
{
	char	*fbd_val;

	fbd_val = get_fbd_values(tk->prev);
	if (!tk->value)
		return (true);
	if (pc < 0 || ft_strstr(fbd_val, tk->value))
		return (sperr(data, UNTOK, tk->value, 2), true);
	if (tk->next && tk->type == RED_OP && tk->next->type != WORD)
		return (sperr(data, UNTOK, tk->next->value, 2), true);
	return (false);
}
/*checks performed :
 * if token value is NULL (unclosed quote)
 * if more open par than closed par
 * if a red_op is followed by anything else than a word
 * if the first token is (pipe|or|and)
 * if a (pipe|or|and) is followed by another (pipe|or|and) or a closed par
 * if an open par is followed by a closed one or by (pipe|or|and)
 * if a closed par is followed by a word
 */
/*int	token_error(t_data *data, t_token *tk, int pc)
{
	if (!tk->value)
		return (true);
	if (pc < 0)
		return (sperr(data, UNTOK, tk->value, 2), true);
	if (tk->type == RED_OP && tk->next->type != WORD)
		return (sperr(data, UNTOK, tk->next->value, 2), true);
	if (!tk->prev && (tk->op == PIPE || tk->op == AND_OP || tk->op == OR_OP))
		return (sperr(data, UNTOK, tk->value, 2), true);
	if (tk->prev && (tk->prev->op == PIPE || tk->prev->op == AND_OP
			|| tk->prev->op == OR_OP) && (tk->op == PIPE || tk->op == OR_OP
			|| tk->op == AND_OP || tk->op == C_PAR))
		return (sperr(data, UNTOK, tk->value, 2), true);
	if (tk->prev && tk->prev->op == O_PAR && (tk->op == C_PAR
		|| tk->op == PIPE || tk->op == OR_OP || tk->op == AND_OP))
		return (sperr(data, UNTOK, tk->value, 2), true);
	if (tk->prev && tk->prev->op == C_PAR && tk->type == WORD)
		return (sperr(data, UNTOK, tk->value, 2), true);
	return (false);
}*/

/**
 * @brief Check syntax error and end using the previously parsed token
 * @param data the main data struct
 * @param tk current token
 * @return the syntaxt status
 */
int	check_syntax(t_data *data, t_token *tk, int *par)
{
	if (tk->op == O_PAR)
		(*par)++;
	else if (tk->op == C_PAR)
		(*par)--;
	if (token_error(data, tk, *par))
	{
		*par = 0;
		return (put_sperr(data->error), data->stx = ERROR);
	}
	else if (tk->op == NEWLINE && (*par > 0
		|| (tk->prev && (tk->prev->op == PIPE || tk->prev->op == OR_OP
		|| tk->prev->op == AND_OP))))
		return (data->stx = NO_END);
	else if (tk->op == NEWLINE)
		return (data->stx = END);
	return (data->stx = CORRECT);
}