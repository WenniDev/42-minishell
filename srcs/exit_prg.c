//	NORM
//		-missing header

#include "spash.h"
#include "spash_error.h"
#include <stdlib.h>

/**
 * @brief Print error if any and exit with data status
 * @param data the main struct
 * @return return of exit()
 */
int exit_prg(t_data *data)
{
	if (data->error.num)
		put_sperr(data->error);
	cleanup(data);
	exit(data->exit_status);
}
