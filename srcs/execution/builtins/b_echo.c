/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:35:46 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/22 11:56:26 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

typedef struct s_echo
{
	int	word;
	int	no_new_line;
	int	param_end;
}	t_echo;

int	is_parameter(char *str, char param)
{
	if (*str++ != '-')
		return (0);
	while (*str == param)
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

int	b_echo(void *data, int argc, char **argv)
{
	t_echo		info;

	(void)data;
	ft_memset(&info, 0, sizeof(t_echo));
	info.word++;
	while (info.word < argc)
	{
		if (is_parameter(argv[info.word], 'n') && !info.param_end)
		{
			info.word++;
			info.no_new_line = 1;
			continue ;
		}
		info.param_end = 1;
		if (sfprint(argv[info.word], false) == -1)
			return (print_error(strerror(errno), "echo", "write error"));
		if (info.word++ < argc - 1)
			if (sfprint(" ", false) == -1)
				return (print_error(strerror(errno), "echo", "write error"));
	}
	if (!info.no_new_line)
		if (sfprint("\n", false) == -1)
			return (print_error(strerror(errno), "echo", "write error"));
	return (0);
}