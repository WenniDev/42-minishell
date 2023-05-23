#include "minishell_builtins.h"
#include "minishell.h"

int	b_env(void *data, int argc, char **argv)
{
	int		i;
	t_exec	*e;

	(void)argc;
	(void)argv;
	e = &((t_data *)data)->exec;
	i = 0;
	while (e->env && e->env[i])
	{
		if (sfprint(e->env[i], 1) == -1)
			return (print_error(strerror(errno), "env", "write error"));
		i++;
	}
	return (EXIT_SUCCESS);
}
