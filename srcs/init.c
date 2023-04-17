//  NORM
//      -missing header

#include "spash.h"
#include "spash_parsing.h"
#include "libft.h"

/**
 * @brief init to 0 the data struct, affect value to grammar table and cmd_line
 * @param data the main data struct
 */
void	init(t_data *data)
{
	if (data)
	{
		ft_memset(data, 0, sizeof (t_data));
		data->c_line = EMPTY;
	}
}
