//	NORM
//		-missing header

#include "spash_types.h"
#include "spash_error.h"
#include "libft.h"

void	uncquote_error(t_data *data, char quote)
{
	char	infos[2];

	infos[0] = quote;
	infos[1] = '\0';
	sperr(data, UNCQUOTE, infos, 2);
}

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
 * @brief Print last encountered error
 * @param error
 */
void	put_sperr(t_error error)
{
	ft_putstr_fd("spash: ", 2);
	if (error.msg)
	{
		ft_putstr_fd(error.msg, 2);
		if (error.infos)
		{
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(error.infos, 2);
		}
		ft_putchar_fd('\n', 2);
	}
}
