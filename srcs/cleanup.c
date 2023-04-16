//	NORM
//		-missing header

#include "spash_types.h"
#include "libft.h"

void	clean_red(t_red *red)
{
	t_red	*next;

	while (red)
	{
		next = red->next;
		if (red->file)
		{
			free(red->file);
		}
		red = next;
	}
}

void	clean_argv(char **argv)
{
	int	i;

	i = 0;
	if (argv)
	{
		while (argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
	}
}

void	clean_cmd(t_cmd *c_table, int c_nb)
{
	int i;

	i = 0;
	while (i < c_nb)
	{
		if (c_table[i].type == SIMPLE_CMD || c_table[i].type == BUILTIN)
		{
			clean_argv(c_table[i].cmd.simple_cmd.argv);
			clean_red(c_table[i].cmd.simple_cmd.outred);
			clean_red(&c_table[i].cmd.simple_cmd.inred);
		}
		if (c_table[i].type == SUBCMD)
		{
			free(c_table[i].cmd.subcmd.line);
			clean_red(c_table[i].cmd.subcmd.outred);
			clean_red(&c_table[i].cmd.subcmd.inred);
		}
		i++;
	}
}

void	cleanup(t_data *data)
{
	if (data->c_line)
	{
		free(data->c_line);
	}
	if (data->c_table)
	{
		clean_cmd(data->c_table, data->c_nb);
	}
	ft_memset(data, 0, sizeof (t_data));
}
