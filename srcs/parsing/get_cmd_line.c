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
	if (!data->c_line)
		data->c_line = readline("spash$ ");
	else if (data->c_line)
	{
		free(data->c_line);
		data->c_line = readline("> ");
		if (!data->c_line)
			return (sperr(data, UNEOF, NULL, 2), NULL);
	}
	if (data->c_line && *data->c_line)
		add_history(data->c_line);
	return (data->c_line);
}
