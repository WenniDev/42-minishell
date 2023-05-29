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

int	b_pwd(void *data, int argc, char **argv)
{
	char	*dir;

	(void)data;
	(void)argc;
	(void)argv;
	dir = getcwd((char *) NULL, 0);
	if (dir == NULL)
		malloc_error();
	if (sfprint(dir, 1) == -1)
		return (print_error(strerror(errno), "pwd", "write error"), 1);
	free(dir);
	return (EXIT_SUCCESS);
}
