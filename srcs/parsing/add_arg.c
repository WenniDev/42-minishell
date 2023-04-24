//	NORM
//		-missing header

#include "spash_parsing.h"
#include "spash_error.h"
#include "spash.h"
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

char	*get_path(t_data *data, t_cmd *cmd, char *cmd_name)
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
	if (access(bin, X_OK) == ERROR)
		cmd->errnum = 126;
	if (!ft_strcmp(bin, NOT_FOUND))
		cmd->errnum = 127;
	return (bin);
}

void	add_arg(t_data *data, t_cmd *cmd, char *arg)
{
	char	**new_argv;

	new_argv = (char **)ft_calloc(cmd->argc + 2, sizeof (char *));
	if (!new_argv)
		(sperr(data, MFAIL, "add_arg", 139), exit_prg(data));
	ft_memcpy(new_argv, cmd->argv, cmd->argc * sizeof (char *));
	free(cmd->argv);
	if (cmd->argc == 0 && ft_strstr(BUILTINS, arg))
		cmd->type = BUILTIN;
	else if (cmd->argc == 0)
		cmd->type = SIMPLE_CMD;
	if (cmd->argc == 0 && cmd->type == SIMPLE_CMD)
		cmd->path = get_path(data, cmd, arg);
	new_argv[cmd->argc] = ft_strdup(arg);
	if (!new_argv[cmd->argc])
		(sperr(data, MFAIL, "add_arg", 139), exit_prg(data));
	cmd->argc++;
	cmd->argv = new_argv;
}
