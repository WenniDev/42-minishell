#include "minishell_builtins.h"

int	b_env(t_exec *e, int argc, char **argv)
{
	int		i;

	(void)argc;
	(void)argv;
	i = 0;
	while (e->env && e->env[i])
		ft_printf("%s\n", e->env[i++]);
	return (EXIT_SUCCESS);
}
