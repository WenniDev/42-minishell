//	NORM
//		-missing header

#include "spash.h"
#include "spash_error.h"
#include "spash_exec.h"
#include <stdbool.h>
#include "libft.h"

void	exec_subcmd(t_data *data, t_cmd cmd)
{
	char	*subcmd_line;

	subcmd_line = ft_strdup(cmd.subcmd_line);
	if (!subcmd_line)
	{
		sperr(data, MFAIL, "exec_cmd", 139);
		exit_prg(data);
	}
	reset(data);
	data->c_line = subcmd_line;
	spash(data, 1);
}

void	exec_cmd(t_data *data, t_cmd cmd, bool exec)
{
	if (!exec)
		exit_prg(data);
	if (cmd.type == SIMPLE_CMD)
		cmd.path = get_path(data, cmd.argv[0]);
	if (cmd.type == SUBCMD)
		exec_subcmd(data, cmd);
	else if (cmd.type == SIMPLE_CMD)
	{
		if (execve(cmd.path, cmd.argv, data->env) == ERROR)
			(sperr(data, NULL, cmd.argv[0], 2), exit_prg(data));
	}
	exit_prg(data);
}
