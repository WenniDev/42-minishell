/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:35:46 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/31 13:22:29 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

int	is_parameter(char *str, char param)
{
	if (!str || !*str)
		return (0);
	if (*str++ != '-')
		return (0);
	while (*str == param)
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

int	b_echo(void *data, t_word_lst *wl, int wnb)
{
	t_echo		info;

	ft_memset(&info, 0, sizeof(t_echo));
	info.word++;
	wl = wl->next;
	while (wl)
	{
		if (is_parameter(wl->word->lval, 'n') && !info.param_end)
		{
			info.word++;
			wl = wl->next;
			info.no_new_line = 1;
			continue ;
		}
		info.param_end = 1;
		if (sfprint(wl->word->lval, false) == -1)
			return (print_error(strerror(errno), "echo", "write error"), 1);
		if (info.word++ < wnb - 1 && wl->word->lval)
			if (sfprint(" ", false) == -1)
				return (print_error(strerror(errno), "echo", "write error"), 1);
		wl = wl->next;
	}
	if (!info.no_new_line && sfprint("\n", false) == -1)
		return (print_error(strerror(errno), "echo", "write error"), 1);
	return ((void)data, 0);
}
