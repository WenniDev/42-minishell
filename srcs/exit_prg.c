//	NORM
//		-missing header

#include "spash_types.h"
#include "spash.h"
#include <stdlib.h>

/**
 * @brief Print error if any and exit with data status
 * @param data the main struct
 * @return return of exit()
 */
int exit_prg(t_data *data) {
	if (data->error.num)
	{
		put_sperr(data->error);
	}
	exit(data->exit_status);
}
