//	NORM
//		-missing header

#include "spash_types.h"
#include "libft.h"

void	clean_tokens(t_data *data)
{
	t_token	*next;
	t_token *tk;

	tk = data->tk_lst;
	while (tk)
	{
		next = tk->next;
		if (tk->type == WORD)
			free(tk->value);
		free(tk);
		tk = next;
	}
	data->tk_lst = NULL;
}

void	clean_red(t_red *red)
{
	t_red	*next;

	while (red)
	{
		next = red->next;
		if (red->file)
			free(red->file);
		free(red);
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

void	clean_cmd(t_cmd *c_table, size_t c_nb)
{
	size_t i;

	i = 0;
	while (i < c_nb)
	{
		if (c_table[i].subcmd_line)
			free(c_table[i].subcmd_line);
		clean_red(c_table[i].io_red);
		clean_argv(c_table[i].argv);
		i++;
	}
	free(c_table);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	if (data->grammar)
		free(data->grammar);
	if (data->c_line)
		free(data->c_line);
	if (data->tk_lst)
		clean_tokens(data);
	if (data->c_table)
		clean_cmd(data->c_table, data->c_nb);
	while (i < 4)
	{
		if (data->fds[i] > 0)
			close(data->fds[i]);
		i++;
	}
	ft_memset(data, 0, sizeof (t_data));
}
