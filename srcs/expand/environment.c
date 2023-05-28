/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:45:15 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/29 01:01:31 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_command.h"
#include "minishell_expand.h"
#include "minishell_utils.h"
#include "libft.h"
#include "signal.h"
#include "stdio.h"

static int	get_mode(int flag, char c, int *curr_mode)
{
	int	new_mode;

	new_mode = M_DEFAULT;
	if (flag & W_IGNORE)
		return (0);
	if (c == '\'')
		new_mode = M_SINGLE;
	if (c == '"')
		new_mode = M_DOUBLE;
	if (new_mode != M_DEFAULT && *curr_mode == M_DEFAULT)
		*curr_mode = new_mode;
	else if (*curr_mode == new_mode)
		*curr_mode = M_DEFAULT;
	return (*curr_mode);
}

static char	*add_res(char *str, char *tmp)
{
	char	*res;

	res = ft_strjoin(str, tmp);
	ft_free((void **)&tmp);
	ft_free((void **)&str);
	if (!res)
	{
		ft_putstr_fd("Malloc failed", 2);
		kill(0, SIGABRT);
	}
	return (res);
}

static char	*get_str(char *str, int *index)
{
	int		i;
	char	*res;

	i = 0;
	if (str[0] == '$' || str[0] == '"' || str[0] == '\'')
		++i;
	while (str[i] && str[i] != '$' && str[i] != '"' && str[i] != '\'')
		++i;
	res = sfcalloc(i + 1, sizeof(char));
	ft_memcpy(res, str, i);
	res[i] = '\0';
	*index += i;
	return (res);
}

static char	*get_env(char *str, int *index, int *flags, int ls)
{
	int		i;
	char	*res;
	char	*var;

	i = 1;
	if (str[i] == '?')
	{
		res = ft_itoa(ls);
		++i;
	}
	else
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		var = sfcalloc(i + 1, sizeof(char));
		ft_memcpy(var, str + 1, i - 1);
		res = ft_strdup(getenv(var));
		if (getenv("IFS") && ft_strpbrk(getenv(var), getenv("IFS")))
			*flags |= W_CHECKISF;
		free(var);
	}
	*index += i;
	return (res);
}

void	expand_env(t_word_d *word, int *status, int ls)
{
	int		i;
	char	*res;
	char	*tmp;
	int		mode;

	i = 0;
	res = NULL;
	mode = 0;
	if (expand_special(word))
		return ;
	while (word->lval[i] && !*status)
	{
		get_mode(word->flags, word->lval[i], &mode);
		if (word->lval[i] == '$' && mode != M_SINGLE)
			tmp = get_env(&word->lval[i], &i, &word->flags, ls);
		else
			tmp = get_str(&word->lval[i], &i);
		if (!tmp)
			*status = 1;
		else
			res = add_res(res, tmp);
	}
	free(word->lval);
	word->lval = res;
	*status = 0;
}
