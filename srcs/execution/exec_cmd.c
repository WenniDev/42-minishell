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
	cleanup(data);
	init(data);
	data->c_line = subcmd_line;
	spash(data, 1);
}

void	exec_cmd(t_data *data, t_cmd cmd, bool exec)
{
	if (!exec)
		exit_prg(data);
	if (cmd.errnum == 127)
		(sperr(data, CMDNOTF, cmd.argv[0], 127), exit_prg(data));
	if (cmd.errnum == 126)
		(sperr(data, PERMDN, cmd.argv[0], 126), exit_prg(data));
	if (cmd.type == BUILTIN)
		exec_builtin(data, cmd);
	if (cmd.type == SUBCMD)
		exec_subcmd(data, cmd);
	else if (cmd.type == SIMPLE_CMD)
	{
		if (execve(cmd.path, cmd.argv, __environ) == ERROR)
			(sperr(data, NULL, cmd.argv[0], 2), exit_prg(data));
	}
	exit_prg(data);
}
