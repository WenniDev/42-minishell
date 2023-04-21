//  NORM
//      -missing header

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
 * @brief init to 0 the data struct, affect value to grammar table and cmd_line
 * @param data the main data struct
 */
void	init(t_data *data)
{
	ft_memset(data, 0, sizeof (t_data));
	data->grammar = create_grammar(data);
	data->c_line = EMPTY;
}
