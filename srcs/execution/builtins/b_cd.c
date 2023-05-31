/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:07:14 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/29 16:13:19 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"
#include "minishell.h"

int	chdir_custom_error(char *dir)
{
	if (errno == ESTALE)
		errno = ENOENT;
	print_error(strerror(errno), "cd", dir);
	return (1);
}

int	b_cd(void *data, t_word_lst *wl, int wnb)
{
	char	*dir;
	t_exec	*e;

	if (wnb > 2)
		return (print_error(ERARGC, "cd", NULL), 1);
	e = &((t_data *)data)->exec;
	dir = getenv("PWD");
	export_var("OLDPWD", dir, e);
	if (wnb == 1 && chdir(getenv("HOME")) == -1)
		return (print_error(ERHOME, "cd", NULL), 1);
	if (wnb > 1 && chdir(wl->next->word->lval) != 0)
		return (chdir_custom_error(wl->next->word->lval));
	dir = getcwd((char *) NULL, 0);
	if (!dir)
		malloc_error();
	export_var("PWD", dir, e);
	ft_free((void **)&((t_data *)data)->xpwd);
	((t_data *)data)->xpwd = ft_strdup(getenv("PWD"));
	free(dir);
	return (0);
}
