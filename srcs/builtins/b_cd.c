//	NORM
//		-missing header

#include "spash_builtins.h"
#include "spash.h"
#include "libft.h"
#include "spash_error.h"

int	b_cd(int argc, char **argv, void *ptr)
{
	char	*dir;
	t_data	*data;

	data = (t_data *)ptr;
	dir = getcwd((char *) NULL, 0);
	if (!dir)
		return (sperr(data, MFAIL, NULL, 139), 139);
//	msh_export_one("OLDPWD", dir, data);
	free(dir);
	if (argc && chdir(argv[1]) != 0)
	{
		sperr(data, NULL, "cd", errno);
		return (errno);
	}
	dir = getcwd((char *) NULL, 0);
	if (!dir)
		return (sperr(data, MFAIL, NULL, 139), 139);
//	msh_export_one("PWD", dir, data);
	free(dir);
	return (0);
}
