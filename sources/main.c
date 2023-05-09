#include <stdlib.h>
#include "minishell.h"

int	main(int argc, char **argv)
{
	t_data	*msh;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	msh = (t_data *)sfcalloc(1, sizeof (t_data));
	signal_handler(msh);
	parse(&msh->parser, 0);
	return (EXIT_SUCCESS);
}
