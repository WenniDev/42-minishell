/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:45:15 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/12 15:04:24 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_command.h"
#include "minishell_utils.h"
#include "libft.h"
#include "signal.h"
#include "stdio.h"

#define debug_print(fmt, ...) \
        do { fprintf(stderr, "\e[1;34m%s\e[1;0m:\e[1;32m%d\e[1;0m:\e[1;0m\e[1;36m%s()\e[1;0m:	" fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

#define M_DEFAULT 0x00
#define M_SINGLE 0x01
#define M_DOUBLE 0x02

int get_mode(char c, int *curr_mode)
{
	int	new_mode;

	new_mode = M_DEFAULT;
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

char	*add_res(char *str, char *tmp)
{
	char	*res;

	res = ft_strjoin(str, tmp);
	free(tmp);
	if (!res)
	{
		ft_putstr_fd("Malloc failed", 2);
		kill(0, SIGABRT);
	}
	return (res);
}

char	*get_str(char *str, int *index)
{
	int		i;
	char	*res;

	i = 0;
	if (str[0] == '$' || str[i] == '"' || str[i] == '\'')
		++i;
	while (str[i] && str[i] != '$' && str[i] != '"' && str[i] != '\'')
		++i;
	res = sfcalloc(i + 1, sizeof(char));
	ft_memcpy(res, str, i);
	*index += i;
	debug_print("added str: %s\n", res);
	return (res);
}

char	*get_env(char *str, int *index)
{
	int		i;
	char	*res;
	char	*var;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var = sfcalloc(i + 1, sizeof(char));
	ft_memcpy(var, str + 1, i - 1);
	res = ft_strdup(getenv(var));
	*index += i;
	debug_print("added env: %s\n", res);
	return (res);
}

void	expand_env(t_word_d *word, int *status)
{
	int		i;
	char	*res;
	char	*tmp;
	int		mode;

	i = 0;
	res = NULL;
	mode = 0;
	while (word->lval[i])
	{
		char c = word->lval[i]; (void)c;
		get_mode(word->lval[i], &mode);
		if (word->lval[i] == '$' && mode != M_SINGLE)
			tmp = get_env(&word->lval[i], &i);
		else
			tmp = get_str(&word->lval[i], &i);
		res = add_res(res, tmp);
	}
	debug_print("res = %s\n", res);
	*status = 0;
}
