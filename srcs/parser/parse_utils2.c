#include "minishell_parse.h"

static const char	*g_builtins[7] = {
	"pwd", "echo", "exit", "env", "unset", "export", "cd"
};

t_red	*ft_last_red(t_red *r)
{
	if (!r)
		return (NULL);
	if (!r->next)
		return (r);
	return (ft_last_red(r->next));
}

int	ft_is_builtin(char *s)
{
	int	i;

	i = 0;
	while(i < 7)
	{
		if (!ft_strcmp(s, g_builtins[i]))
			return (1);
		i++;
	}
	return (0);
}
