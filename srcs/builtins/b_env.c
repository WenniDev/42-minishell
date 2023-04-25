//	NORM
//		-missing header

#include "spash_builtins.h"
#include "spash_environ.h"
#include "libft.h"

int	b_env(int argc, char **argv, void *ptr)
{
	int		i;
	t_data	*data;

	(void)argc;
	(void)argv;
	data = (t_data *)ptr;
	i = 0;
	while (data->env && data->env[i])
		ft_printf("%s\n", data->env[i++]);
	return (EXIT_SUCCESS);
}