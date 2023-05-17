#include "minishell_builtins.h"


int	b_cd(t_exec *e, int argc, char **argv)
{
	char	*dir;

	(void)e;
	dir = getcwd((char *) NULL, 0);
	if (!dir)
		malloc_error();
//	msh_export_one("OLDPWD", dir, data);
	free(dir);
	if (argc == 1 && chdir(getenv("HOME")) == -1)
		return (print_error(ERHOME, "cd", NULL));
	if (argc > 1 && chdir(argv[1]) != 0)
		return (print_error(strerror(errno), "cd", argv[1]));
	dir = getcwd((char *) NULL, 0);
	if (!dir)
		malloc_error();
//	msh_export_one("PWD", dir, data);
	free(dir);
	return (0);
}
