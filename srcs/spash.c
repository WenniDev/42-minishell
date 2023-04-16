//	NORM
//		-missing header

#include "spash.h"
#include "libft.h"

int	spash(t_data *data, bool subcmd)
{
	if (!data)
	{
		return (EXIT_FAILURE);
	}
	if (subcmd)
	{
//		parse(data);
//		execute(data);
		exit(data->exit_status);
	}
	while (data->c_line)
	{
		get_cmd_line(data);
//		parse(data);
//		execute(data);
//		reset(data);
	}
	exit(data->exit_status);
}