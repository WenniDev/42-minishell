//	NORM
//		-missing header

#include "spash.h"
#include "spash_parsing.h"
#include "libft.h"

void	reset(t_data *data)
{
	cleanup(data);
	data->c_line = EMPTY;
}

/**
 * @brief Get, parse and execute command line then reset if not in subcmd mode
 * @param data the main data struct
 * @param subcmd subcmd flag
 * @return the main exit status
 */
int	spash(t_data *data, bool subcmd)
{
	if (!data)
		return (EXIT_FAILURE);
	if (subcmd)
	{
		parse(data);
//		execute(data);
		exit(data->exit_status);
	}
	while (data->c_line)
	{
		get_cmd_line(data);
		parse(data);
//		execute(data);
		reset(data);
	}
	exit(data->exit_status);
}