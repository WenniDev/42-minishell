//	NORM
//		-missing header

#include "spash_exec.h"
#include "spash_error.h"
#include "libft.h"

int	exec_builtin(t_data *data, t_cmd cmd, int *w_nb)
{
	int	i;

	i = 0;
	(*w_nb)--;
	while (ft_strcmp(cmd.argv[0], data->builtins[i].cmd) && i < 7)
		i++;
	data->exit_status = data->builtins[i].fct(cmd.argc, cmd.argv, data);
	if (data->exit_status)
		put_sperr(data->error);
	return (data->exit_status);
}
