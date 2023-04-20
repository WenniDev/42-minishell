//	NORM
//		-missing header

#include "spash.h"
#include "spash_parsing.h"
#include "spash_error.h"

/**
 * @brief Parse the token list into a cmd table with io_red and conditions
 * @param data the main data struct
 */
void	parse_tokens(t_data *data)
{
	int		par;
	t_token	*tk;

	par = 0;
	tk = data->tk_lst;
	while (tk && check_syntax(data, tk, &par) == CORRECT)
	{
		if (!data->c_nb || (!par && (tk->op == PIPE
			|| tk->op == OR_OP || tk->op == AND_OP)))
			add_cmd(data, tk);
		if (par)
			subcmd(data, &data->c_table[data->c_nb - 1], tk);
		else if (!par && tk->prev && tk->prev->type == RED_OP)
			add_io_red(data, &data->c_table[data->c_nb - 1], tk);
		else if (!par && tk->type == WORD)
			add_arg(data, &data->c_table[data->c_nb - 1], tk->value);
		tk = tk->next;
	}
}

/**
 * @brief Parse the command line into an command table
 * @param data the main data struct
 */
void	parse(t_data *data)
{
	while (data->c_line && data->stx != END && data->stx != ERROR)
	{
		create_tokens(data);
		parse_tokens(data);
		if (data->stx == NO_END)
			get_cmd_line(data);
		clean_tokens(data);
	}
}
