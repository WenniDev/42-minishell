/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:53:29 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/30 22:57:12 by jopadova         ###   ########.fr       */
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

char	**edit_in_env(char *var, char *full_var, t_exec *e)
{
	int		i;
	int		j;
	int		env_size;
	char	**tmp_env;

	j = -1;
	i = get_env_index(e->env, var);
	env_size = 0;
	while (e->env && e->env[env_size])
		env_size++;
	tmp_env = (char **)sfcalloc(env_size + 1, sizeof (char *));
	while (++j < env_size)
		tmp_env[j] = e->env[j];
	free(tmp_env[i]);
	tmp_env[i] = full_var;
	free(e->env);
	return (tmp_env);
}

char	**add_in_env(char *full_var, t_exec *e)
{
	int		j;
	int		env_size;
	char	**tmp_env;

	j = -1;
	env_size = 0;
	while (e->env && e->env[env_size])
		env_size++;
	tmp_env = (char **)sfcalloc(env_size + 2, sizeof (char *));
	while (++j < env_size)
		tmp_env[j] = e->env[j];
	tmp_env[env_size] = full_var;
	tmp_env[env_size + 1] = NULL;
	free(e->env);
	return (tmp_env);
}

void	export_var(char *name, char *value, t_exec *e)
{
	char	*full_var;
	char	*tmp_full_var;

	if (!name || !value)
		return ;
	tmp_full_var = ft_strjoin(name, "=");
	if (!tmp_full_var)
		return (free(name), (void) malloc_error());
	full_var = ft_strjoin(tmp_full_var, value);
	free(tmp_full_var);
	if (!full_var)
		return (free(name), (void) malloc_error());
	if (getenv(name))
		e->env = edit_in_env(name, full_var, e);
	else
		e->env = add_in_env(full_var, e);
	__environ = e->env;
}

/*int	b_export(void *data, t_word_lst *wl, int wnb)
{
	t_word_lst	*tmp;
	int		i;
	char	*name;

	i = 0;
	tmp = wl->next;
	while (tmp)
	{
		if (ft_isdigit(tmp->word->lval[0]))
			return (free(name),
				print_error(EXPFAIL, "export", tmp->word->lval), 1);
		while (tmp->word->lval[i] != '=')
		{
			if (!ft_isalnum(tmp->word->lval[i]) && tmp->word->lval[i] != '_')
				return (free(name),
					print_error(EXPFAIL, "export", tmp->word->lval), 1);
			i++;
		}
		name = ft_substr(tmp->word->lval, i, ft_strlen(tmp->word->lval + i));
		if (!name)
			malloc_error();
		export_var(name, ++argv[i], &((t_data *)data)->exec);
		free(name);
	}
	return (EXIT_SUCCESS);
}*/

int	b_export(void *data, t_word_lst *wl, int wnb)
{
	t_word_lst	*w;
	char		*name;
	char		*val;
	int			i;

	w = wl->next;
	while (w && wnb)
	{
		i = -1;
		while (w->word->lval[++i] != '=')
		{
			if (ft_isdigit(w->word->lval[0])
				|| (!ft_isalnum(w->word->lval[i]) && w->word->lval[i] != '_'))
				return (print_error(EXPFAIL, "export", w->word->lval), 1);
		}
		val = ft_substr(w->word->lval, i + 1, ft_strlen(w->word->lval + i));
		if (!val)
			malloc_error();
		name = ft_substr(w->word->lval, 0, i);
		if (!name)
			(free(val), malloc_error());
		(export_var(name, val, &((t_data *)data)->exec), free(name), free(val));
		w = w->next;
	}
	return (0);
}
