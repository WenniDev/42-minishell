#include "minishell_builtins.h"

int	b_env(t_exec *e, int argc, char **argv)
{
	int		i;

	(void)argc;
	(void)argv;
	i = 0;
	while (e->env && e->env[i])
	{
		if (sfprint(e->env[i], 1) == -1)
			return (print_error(strerror(errno), "env", "write error"));
		i++;
	}
	return (EXIT_SUCCESS);
}
