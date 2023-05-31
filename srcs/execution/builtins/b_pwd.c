/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:42:29 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/29 16:06:43 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"
#include "minishell.h"

int	b_pwd(void *data, t_word_lst *wl, int wnb)
{
	char	*dir;
	t_data	*msh;

	(void)wl;
	(void)wnb;
	msh = (t_data *)data;
	dir = getenv("PWD");
	if (!dir)
		dir = msh->xpwd;
	if (sfprint(dir, 1) == -1)
		return (print_error(strerror(errno), "pwd", "write error"), 1);
	return (EXIT_SUCCESS);
}
