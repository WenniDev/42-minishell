//	NORM
//		-missing header

#include "spash_types.h"
#include "libft.h"

/**
 * @brief Store error infos in error struct and update exit status
 * @param data main data structure
 * @param msg error msg
 * @param infos infos about the error
 * @param errnum error number
 */
void	sperr(t_data *data, char *msg, char *infos, int errnum)
{
	if (data)
	{
		data->error.msg = msg;
		data->error.infos = infos;
		data->error.num = errnum;
		data->exit_status = errnum;
	}
}

/**
 * @brief Print last encountered error. Call perror() if msg is NULL
 * @param error
 */
void	put_sperr(t_error error)
{
	if (error.msg)
	{
		if (error.infos)
		{
			ft_putstr_fd(error.infos, 2);
			ft_putchar_fd(':', 2);
		}
		ft_putstr_fd(error.msg, 2);
		ft_putchar_fd('\n', 2);
	}
	else if (error.num)
	{
		perror(error.infos);
	}
}
