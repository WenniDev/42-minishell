//	NORM
//		-missing header

#include "spash_exec.h"
#include "spash_error.h"
#include "libft.h"

int	exec_builtin(t_data *data, t_cmd cmd)
{
	int	i;

	i = 0;
	while (ft_strcmp(cmd.argv[0], data->builtins[i].cmd) && i < 7)
		i++;
	data->exit_status = data->builtins[i].fct(cmd.argc, cmd.argv, data);
	return (data->exit_status);
}
