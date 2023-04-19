//	NORM
//		-missing header

#include "spash_types.h"
#include "spash_error.h"
#include "spash.h"
#include "libft.h"

t_red	*last_red(t_red *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_io_red(t_data *data, t_cmd *cmd, t_token *tk)
{
	t_red	*red;

	red = (t_red *)ft_calloc(1, sizeof (t_red));
	if (!red)
		(sperr(data, MFAIL, "add_io_red", 2), exit_prg(data));
	red->file = ft_strdup(tk->value);
	if (!red->file)
		(sperr(data, MFAIL, "add_io_red", 2), exit_prg(data));
	red->op = tk->op;
	if (red->op == OUTTR_RED)
		red->flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (red->op == OUTAP_RED)
		red->flags = O_CREAT | O_WRONLY | O_APPEND;
	if (!cmd->io_red)
		cmd->io_red = red;
	else
		last_red(cmd->io_red)->next = red;
}
