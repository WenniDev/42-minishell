//	NORM
//		-missing header

#include "spash_types.h"
#include "spash_error.h"
#include "spash.h"
#include "libft.h"

void	add_arg(t_data *data, t_cmd *cmd, char *arg)
{
	char	**new_argv;

	new_argv = (char **)ft_calloc(cmd->argc + 2, sizeof (char *));
	if (!new_argv)
		(sperr(data, MFAIL, "add_arg", 2), exit_prg(data));
	ft_memcpy(new_argv, cmd->argv, cmd->argc * sizeof (char *));
	free(cmd->argv);
	new_argv[cmd->argc] = ft_strdup(arg);
	if (!new_argv[cmd->argc])
		(sperr(data, MFAIL, "add_arg", 2), exit_prg(data));
	cmd->argc++;
	cmd->argv = new_argv;
}
