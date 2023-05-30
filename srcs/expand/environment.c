/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:45:15 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/30 23:18:11 by jopadova         ###   ########.fr       */
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

static char	*get_env(char *str, int *index, t_expand *exp, int ls)
{
	int		i;
	char	*res;
	char	*var;

	i = 1;
	if (str[i] == '?')
		return (*index += ++i, res = ft_itoa(ls));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 1 && (exp->mode & (M_DOUBLE | M_SINGLE)))
		res = ft_strdup("$");
	else
	{
		var = sfcalloc(i + 1, sizeof(char));
		ft_memcpy(var, str + 1, i - 1);
		res = ft_strdup(getenv(var));
		if (getenv("IFS") && ft_strpbrk(getenv(var), getenv("IFS")))
			exp->word->flags |= W_CHECKISF;
		free(var);
	}
	*index += i;
	return (res);
}

void	expand_env(t_word_d *word, int *status, int ls)
{
	int			i;
	char		*tmp;
	t_expand	exp;

	i = 0;
	exp.res = NULL;
	exp.mode = 0;
	exp.word = word;
	if (expand_special(word))
		return ;
	while (word->lval[i] && !*status)
	{
		get_mode(word->flags, word->lval[i], &exp.mode);
		if (word->lval[i] == '$' && exp.mode != M_SINGLE)
			tmp = get_env(&word->lval[i], &i, &exp, ls);
		else
			tmp = get_str(&word->lval[i], &i);
		if (!tmp)
			*status = 1;
		else
			exp.res = add_res(exp.res, tmp);
	}
	free(word->lval);
	word->lval = exp.res;
	*status = 0;
}
