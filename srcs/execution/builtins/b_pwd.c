#include "minishell_builtins.h"

int	b_pwd(void *data, int argc, char **argv)
{
	char	*dir;

	(void)data;
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
