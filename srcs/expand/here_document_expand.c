#include "minishell_command.h"
#include "minishell_expand.h"

char *here_document_expand(int ls, t_red *r, int *len)
{
	int status;

	status = 0;
	if (r->filename->lval == 0 || r->filename->lval[0] == '\0')
	{
		if (len)
			*len = 0;
		return (r->filename->lval);
	}
	if (r->filename->flags & W_NOEXPAND)
	{
		if (len)
			*len = (int)ft_strlen(r->filename->lval);
		return (r->filename->lval);
	}
	expand_env(r->filename, &status, ls);
	if (len)
		*len = (int)ft_strlen(r->filename->lval);
	return (r->filename->lval);
}
