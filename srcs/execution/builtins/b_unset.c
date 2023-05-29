/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:04:31 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/29 16:06:55 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"
#include "minishell.h"

static int	get_env_index(char **env, char *var)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var) + 1) == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	unset_var(t_exec *e, char *var)
{
	int		i;
	int		j;
	int		env_size;
	char	**tmp_env;

	j = -1;
	i = get_env_index(e->env, var);
	if (i == -1)
		return ;
	env_size = 0;
	while (e->env && e->env[env_size])
		env_size++;
	tmp_env = (char **)sfcalloc(env_size, sizeof (char *));
	while (++j < i)
		tmp_env[j] = e->env[j];
	free(e->env[i]);
	while (j + 1 < env_size)
	{
		tmp_env[j] = e->env[j + 1];
		j++;
	}
	free(e->env);
	e->env = tmp_env;
	__environ = tmp_env;
}

int	b_unset(void *data, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc && argv[i])
	{
		unset_var(&((t_data *)data)->exec, argv[i]);
		i++;
	}
	return (0);
}
