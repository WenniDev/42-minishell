//	NORM
//		-missing header

#include "spash_builtins.h"
#include "libft.h"

int	b_pwd(int argc, char **argv, void *data)
{
	char	*dir;

	(void)argc;
	(void)argv;
	dir = getcwd((char *) NULL, 0);
	if (dir == NULL)
		return (sperr((t_data *)data, MFAIL, NULL, errno), 139);
	ft_printf("%s\n", dir);
	free(dir);
	return (EXIT_SUCCESS);
}
