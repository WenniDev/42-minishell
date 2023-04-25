//	NORM
//		-missing header

#include "spash.h"
#include "spash_error.h"
#include <stdlib.h>
#include "libft.h"

/**
 * @brief Print error if any and exit with data status
 * @param data the main struct
 * @return return of exit()
 */
int exit_prg(t_data *data)
{
	ft_printf("exit status = %d\n", data->error.num);
	if (data->error.num)
		put_sperr(data->error);
	cleanup(data, 1);
	exit(data->exit_status);
}
