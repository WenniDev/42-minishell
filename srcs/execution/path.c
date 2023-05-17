#include "minishell.h"

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

char *get_binary(char **paths, char *cmd_name)
{
	int		i;
	char 	*tmp;
	char	*bin;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			(free_split(paths), malloc_error());
		bin = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (!bin)
			(free_split(paths), malloc_error());;
		if (access(bin, F_OK) == 0)
			return (bin);
		i++;
	}
	return (NULL);
}

char	*get_path(t_data *msh, char *cmd_name)
{
	char	**paths;
	char	*bin;

	paths = ft_split(getenv("PATH"), ":");
	if (!paths)
		malloc_error();
	if (*cmd_name == '.' || *cmd_name == '/' || *cmd_name == '~')
		bin = ft_strdup(cmd_name);
	else
		bin = get_binary(paths, cmd_name);
	free_split(paths);
	if (!bin)
		(print_error(CMDNOTF, cmd_name, NULL), exit_prg(msh, 127));
	if (access(bin, X_OK) == EXS_ERROR)
		(print_error(CMDPERMD, cmd_name, NULL), exit_prg(msh, 126));
	return (bin);
}
