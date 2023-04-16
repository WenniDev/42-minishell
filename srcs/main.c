//  NORM
//      -missing header

#include "spash.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	init(&data);
	spash(&data, 0);
}
