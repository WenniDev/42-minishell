//	NORM
//		-missing header

#include "spash_types.h"
#include "spash_error.h"
#include "spash_parsing.h"
#include "libft.h"
#include "readline/readline.h"
#include "readline/history.h"

char	*get_cmd_line(t_data *data)
{
	if (!ft_strcmp(data->c_line, EMPTY))
	{
		data->c_line = readline(getenv("PS1"));
		return (data->c_line);
	}
	else if (data->c_line)
	{
		free(data->c_line);
		data->c_line = readline("> ");
		if (!data->c_line)
		{
			sperr(data, UNEOF, NULL, 2);
			return (NULL);
		}
		else if (!*data->c_line)
		{
			add_history(data->c_line);
		}
	}
	return (data->c_line);
}
