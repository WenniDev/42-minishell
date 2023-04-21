//	NORM
//		-missing header

#include "spash_types.h"
#include "spash_error.h"
#include "spash.h"
#include "libft.h"

void	add_cmd(t_data *data, t_token *tk)
{
	t_cmd	*new_table;

	new_table = (t_cmd *)ft_calloc(data->c_nb + 1, sizeof (t_cmd));
	if (!new_table)
		(sperr(data, MFAIL, NULL, 139), exit_prg(data));
	ft_memcpy(new_table, data->c_table, data->c_nb * sizeof (t_cmd));
	free(data->c_table);
	if (tk->op == AND_OP)
		new_table[data->c_nb].exec_if = IF_TRUE;
	if (tk->op == OR_OP)
		new_table[data->c_nb].exec_if = IF_FALSE;
	data->c_nb++;
	data->c_table = new_table;
}
