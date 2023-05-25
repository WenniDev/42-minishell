/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:07:14 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/25 19:24:22 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"
#include "minishell.h"

int	b_cd(void *data, int argc, char **argv)
{
	char	*dir;
	t_exec	*e;

	if (argc > 2)
	{
		print_error(ERARGC, "cd", NULL);
		return (1);
	}
	e = &((t_data *)data)->exec;
	dir = getcwd((char *) NULL, 0);
	if (!dir)
		malloc_error();
	export_var("OLDPWD", dir, e);
	free(dir);
	if (argc == 1 && chdir(getenv("HOME")) == -1)
		return (print_error(ERHOME, "cd", NULL));
	if (argc > 1 && chdir(argv[1]) != 0)
		return (print_error(strerror(errno), "cd", argv[1]));
	dir = getcwd((char *) NULL, 0);
	if (!dir)
		malloc_error();
	export_var("PWD", dir, e);
	free(dir);
	return (0);
}
