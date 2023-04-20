//	NORM
//		-missing header

#include "spash.h"
#include "spash_parsing.h"
#include "libft.h"

void	print_cmds(t_data *data)
{
	t_red	*red;

	for (size_t i = 0; i < data->c_nb; i++)
	{
		if (data->c_table[i].subcmd_line)
			ft_printf("subcmd_line = %s\n", data->c_table[i].subcmd_line);
		red = data->c_table[i].io_red;
		for (int j = 0; j < data->c_table[i].argc; j++)
			ft_printf("argv[%d] = %s\n", j, data->c_table[i].argv[j]);
		if (red)
			ft_printf("io_red: ");
		int k = 1;
		while (red)
		{
			ft_printf("[%d]type: %d file: %s\t", k, red->op, red->file);
			if (!red->next)
				ft_printf("\n");
			red = red->next;
			k++;
		}
		ft_printf("\n");
	}
}

void	reset(t_data *data)
{
	cleanup(data);
	init(data);
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
		exit_prg(data);
	}
	while (data->c_line)
	{
		get_cmd_line(data);
		parse(data);
		print_cmds(data);
//		execute(data);
		reset(data);
	}
	exit(data->exit_status);
}
