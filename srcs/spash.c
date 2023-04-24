//	NORM
//		-missing header

#include "spash.h"
#include "spash_parsing.h"
#include "spash_exec.h"
#include "libft.h"

void	print_cmds(t_data *data)
{
	t_red	*red;

	for (int i = 0; i < data->c_nb; i++)
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
			ft_printf("[%d]type: %d file: %s ", k, red->op, red->file);
			if (!red->next)
				ft_printf("\n");
			red = red->next;
			k++;
		}
		if (data->c_table[i].exec_if)
			ft_printf("exec if : %d\n", data->c_table[i].exec_if);
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
		exec(data);
		exit_prg(data);
	}
	else
	{
		get_cmd_line(data);
		while (data->c_line)
		{
			parse(data);
			print_cmds(data);
			exec(data);
			reset(data);
			get_cmd_line(data);
		}
	}
	exit_prg(data);
	return (0);
}
