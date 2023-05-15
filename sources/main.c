#include <stdlib.h>
#include "minishell.h"

int	parse_and_execute(t_data *msh);
int	execute_cmd_lst(t_data *msh, t_exec *e, t_command_lst *cl);

int	main(int argc, char **argv, char **env)
{
	t_data	*msh;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	msh = (t_data *)sfcalloc(1, sizeof (t_data));
	msh->exec.env = env;
	signal_handler(msh);
	while (!msh->parser.eof)
		parse_and_execute(msh);
	return (msh->status);
}

int	parse_and_execute(t_data *msh)
{
	msh->status = parse(&msh->parser);
	if (!msh->status && !msh->parser.eof)
		msh->status = execute_cmd_lst(msh, &msh->exec, msh->parser.cmd_lst);
	if (!msh->parser.eof)
		reset_parser(&msh->parser);
	return (msh->status);
}

int	exit_prg(t_data *msh, int status)
{
	(void)msh;
	exit(status);
}
