#include "minishell_execute.h"

int	execute(t_exec *e, t_command_lst *cmds)
{
	while (cmds->next)
	{
		e->status = execute_cmd(e, cmds);
		cmds = cmds->next;
	}
	return (e->status);
}

int	execute_cmd(t_exec *e, t_command_lst *cmd)
{
	redirect(e, cmd);
	if (cmd->cmd.type == subshell_cmd)
		return (execute_in_subshell(e, cmd));
	
}