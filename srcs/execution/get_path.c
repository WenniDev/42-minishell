//	NORM
//		-missing header

#include "spash.h"
#include "spash_error.h"
#include "spash_exec.h"
#include "libft.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

char *get_binary(t_data *data, char **paths, char *cmd_name)
{
	int		i;
	char 	*tmp;
	char	*bin;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (sperr(data, MFAIL, "get_binary", 139), NULL);
		bin = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (!bin)
			return (sperr(data, MFAIL, "get_binary", 139), NULL);
		if (access(bin, F_OK) == 0)
			return (bin);
		i++;
	}
	return (NOT_FOUND);
}

char	*get_path(t_data *data, char *cmd_name)
{
	char	**paths;
	char	*bin;

	paths = ft_split(getenv("PATH"), ":");
	if (!paths)
		exit_prg(data);
	if (*cmd_name == '.' || *cmd_name == '/' || *cmd_name == '~')
		bin = ft_strdup(cmd_name);
	else
		bin = get_binary(data, paths, cmd_name);
	if (!bin)
		(free_split(paths), sperr(data, MFAIL, NULL, 139), exit_prg(data));
	free_split(paths);
	if (!ft_strcmp(bin, NOT_FOUND))
		(sperr(data, CMDNOTF, cmd_name, 127), exit_prg(data));
	if (access(bin, X_OK) == ERROR)
		(sperr(data, PERMDN, cmd_name, 126), exit_prg(data));
	return (bin);
}
