/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:01:23 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/12 15:51:36 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int	parse_and_execute(t_data *msh);

int	main(int argc, char **argv)
{
	t_data	*msh;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	msh = (t_data *)sfcalloc(1, sizeof (t_data));
	signal_handler(msh);
	while (!msh->parser.eof)
		parse_and_execute(msh);
	return (msh->status);
}

int execute(t_exec *exec, t_command_lst *command)
{
	(void)exec;
	(void)command;

	return (0);
}

int	parse_and_execute(t_data *msh)
{
	msh->status = parse(&msh->parser);
	if (!msh->status)
		msh->status = expand(msh->parser.cmd_lst->cmd.elem.words);
	if (!msh->status)
		msh->status = execute(&msh->exec, msh->parser.cmd_lst);
	reset_parser(&msh->parser);
	return (msh->status);
}