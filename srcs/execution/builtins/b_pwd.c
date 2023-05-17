#include "minishell_builtins.h"

int	b_pwd(t_exec *e, int argc, char **argv)
{
	char	*dir;

	(void)e;
	(void)argc;
	(void)argv;
	dir = getcwd((char *) NULL, 0);
	if (dir == NULL)
		malloc_error();
	if (sfprint(dir, 1) == -1)
		return (print_error(strerror(errno), "pwd", "write error"));
	free(dir);
	return (EXIT_SUCCESS);
}
