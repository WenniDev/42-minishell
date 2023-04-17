//	NORM
//		-missing header

#include "spash_types.h"
#include "spash_error.h"
#include "spash_parsing.h"
#include "libft.h"
#include "readline/readline.h"
#include "readline/history.h"

/**
 * @brief Get the command line and adds it to history if not empty
 * @param data the main data struct
 * @return the command line
 */
char	*get_cmd_line(t_data *data)
{
	if (!ft_strcmp(data->c_line, EMPTY))
		return (data->c_line = readline(getenv("PS1")));
	else if (data->c_line)
	{
		free(data->c_line);
		data->c_line = readline("> ");
		if (!data->c_line)
			return (sperr(data, UNEOF, NULL, 2), NULL);
		else if (!*data->c_line)
			add_history(data->c_line);
	}
	return (data->c_line);
}
