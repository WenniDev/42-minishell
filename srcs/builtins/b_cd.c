//	NORM
//		-missing header

#include "spash_builtins.h"
#include "spash.h"
#include "libft.h"
#include "spash_error.h"

int	change_dir(int argc, char **argv, t_data *data)
{
	if (argc > 2)
		return (sperr(data, CDTMARG, "cd", 1), 1);
	else if (argc == 1)
	{
		if (!getenv("HOME"))
			return (sperr(data, CDFAIL, "cd", 1), 1);
		if (chdir(getenv("HOME")) != 0)
			return (sperr(data, NULL, "cd", errno), errno);
	}
	else if (argc == 2 && *argv[1] && ft_strcmp(argv[1], "-") == 0)
	{
		if (!getenv("OLDPWD"))
			return (sperr(data, PWDFAIL, "cd", 1), 1);
		if (chdir(getenv("OLDPWD")) != 0)
			return (sperr(data, NULL, "cd", errno), errno);
		printf("%s\n", getenv("OLDPWD"));
	}
	else if (argc == 2 && *argv[1] && chdir(argv[1]) != 0)
		return (sperr(data, NULL, "cd", errno), errno);
	return (0);
}

int	b_cd(int argc, char **argv, void *ptr)
{
	char	*old_dir;
	char	*dir;
	int		exit_code;

	old_dir = getcwd((char *) NULL, 0);
	if (!old_dir)
		return (sperr((t_data *)ptr, MFAIL, NULL, 139), 139);
	exit_code = change_dir(argc, argv, (t_data *)ptr);
	if (exit_code)
		return (exit_code);
	dir = getcwd((char *) NULL, 0);
	if (!dir)
		return (sperr((t_data *)ptr, MFAIL, NULL, 139), 139);
	// msh_export_one("OLDPWD", old_dir, (t_data *)ptr);
	free(old_dir);
	// msh_export_one("PWD", dir, (t_data *)ptr_data);
	free(dir);
	return (0);
}
