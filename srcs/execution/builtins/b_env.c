/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:41:13 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:41:14 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"
#include "minishell.h"

int	b_env(void *data, t_word_lst *wl, int wnb)
{
	int		i;
	t_exec	*e;

	(void)wnb;
	(void)wl;
	e = &((t_data *)data)->exec;
	i = 0;
	while (e->env && e->env[i])
	{
		if (sfprint(e->env[i], 1) == -1)
			return (print_error(strerror(errno), "env", "write error"), 1);
		i++;
	}
	return (EXIT_SUCCESS);
}
