#include "minishell_parse.h"

t_red	*ft_last_red(t_red *r)
{
	if (!r)
		return (NULL);
	if (!r->next)
		return (r);
	return (ft_last_red(r->next));
}
