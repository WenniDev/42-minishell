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

int	parse_and_execute(t_data *msh)
{
	msh->status = parse(&msh->parser);
/*	if (!msh->status)
		msh->status = expand(msh->parser.cmd_lst);
	if (!msh->status)
		msh->status = execute(&msh->exec, msh->parser.cmd_lst);*/
	reset_parser(&msh->parser);
	return (msh->status);
}