//	NORM
//		-missing header

#include "spash_types.h"
#include "spash_parsing.h"
#include <stdbool.h>

t_token	*create_token(t_data *data)
{
	
}

void	parse(t_data *data)
{
	t_token	*token;
	int		syntax_status;

	while (data && data->c_line)
	{
		token = create_token(data);
		syntax_status = check_syntax(data, token);
		if (syntax_status == FALSE || syntax_status == END)
		{
			break ;
		}
		else if (syntax_status == NO_END)
		{
			get_cmd_line(data);
			continue ;
		}
		parse_token(data, token);
	}
}