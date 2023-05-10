/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:45:40 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/10 16:45:41 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execute.h"

//int	execute(t_exec *e, t_command_lst *cmds)
//{
//	while (cmds->next)
//	{
//		e->status = execute_cmd(e, cmds);
//		cmds = cmds->next;
//	}
//	return (e->status);
//}
//
//int	execute_cmd(t_exec *e, t_command_lst *cmd)
//{
//	redirect(e, cmd);
//	if (cmd->cmd.type == subshell_cmd)
//		return (execute_in_subshell(e, cmd));
//
//}