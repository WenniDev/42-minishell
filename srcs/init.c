//  NORM
//      -missing header

#include "spash.h"
#include "spash_parsing.h"
#include "spash_error.h"
#include "spash_exec.h"
#include "spash_builtins.h"
#include "spash_environ.h"
#include "libft.h"

void	init_grammar(t_data *data)
{
	data->grammar = (char **)ft_calloc(11, sizeof (char *));
	if (!data->grammar)
		(sperr(data, MFAIL, "create_grammar", 139), exit_prg(data));
	data->grammar[0] = MUCH_LESS;
	data->grammar[1] = MUCH_GREATER;
	data->grammar[2] = DOUBLE_AMPERSAND;
	data->grammar[3] = DOUBLE_VERTICAL_BAR;
	data->grammar[4] = LESS;
	data->grammar[5] = GREATER;
	data->grammar[6] = VERTICAL_BAR;
	data->grammar[7] = OPENED_PARENTHESIS;
	data->grammar[8] = CLOSED_PARENTHESIS;
	data->grammar[9] = S_NEWLINE;
}

void	init_builtins(t_data *data)
{
	data->builtins = ft_calloc(7, sizeof (t_builtin));
	if (!data->builtins)
	{
		sperr(data, MFAIL, "init_builtin_ft", 139);
		exit_prg(data);
	}
/*	data->builtins[I_EXPORT].cmd = S_EXPORT;
	data->builtins[I_EXPORT].fct = b_export;*/
	data->builtins[I_PWD].cmd = S_PWD;
	data->builtins[I_PWD].fct = b_pwd;
/*	data->builtins[I_UNSET].cmd = S_UNSET;
	data->builtins[I_UNSET].fct = b_unset;*/
	data->builtins[I_CD].cmd = S_CD;
	data->builtins[I_CD].fct = b_cd;
/*	data->builtins[I_EXIT].cmd = S_EXIT;
	data->builtins[I_EXIT].fct = b_exit;
	data->builtins[I_ECHO].cmd = S_ECHO;
	data->builtins[I_ECHO].fct = b_echo;*/
	data->builtins[I_ENV].cmd = S_ENV;
	data->builtins[I_ENV].fct = b_env;
}

/**
 * @brief init to 0 the data struct, affect value to grammar table and cmd_line
 * @param data the main data struct
 */
void	init(t_data *data)
{
	ft_memset(data, 0, sizeof (t_data));
	init_env(data);
	init_grammar(data);
	init_builtins(data);
}
