//	NORM
//		-missing header

#include "spash_builtins.h"
#include "libft.h"

int	b_env(int argc, char **argv, void *ptr)
{
	int		i;

	(void)argc;
	(void)argv;
	(void)ptr;
	i = 0;
	while (__environ && __environ[i])
		ft_printf("%s\n", __environ[i++]);
	return (EXIT_SUCCESS);
}