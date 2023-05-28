/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:59:59 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/28 17:11:33 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_env.h"
#include "minishell_execute.h"
#include "minishell_builtins.h"

void	new_environ(t_exec *e)
{
	char	*path;

	e->env = ft_split(DEFAULT_ENV, ENV_SEP);
	if (!e->env)
		malloc_error();
	path = ft_strdup(PTH);
	if (!path)
		malloc_error();
	free(e->env[0]);
	e->env[0] = path;
}

void	copy_environ(t_exec *e)
{
	int	i;
	int	env_size;

	i = 0;
	env_size = 0;
	while (__environ && __environ[env_size])
		env_size++;
	e->env = (char **)sfcalloc(env_size + 1, sizeof (char *));
	while (i < env_size)
	{
		e->env[i] = ft_strdup(__environ[i]);
		if (!e->env[i])
			malloc_error();
		i++;
	}
}

void	init_env(t_exec *e)
{
	if (!__environ || !*__environ)
		new_environ(e);
	else
		copy_environ(e);
	__environ = e->env;
	export_var("IFS", "\n\t ", e);
}
