/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:41:26 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:41:43 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"
#include "minishell.h"
#include <limits.h>

#define LL_MAX 0x7FFFFFFFFFFFFFFF
#define LL_MIN 0x8000000000000000

int			only_digits(char *s);
long long	ft_atoll(char *s);

int	b_exit(void *data, int argc, char **argv)
{
	t_data		*msh;
	long long	exstat;

	msh = (t_data *)data;
	if (msh->exec.child == false)
		printf("exit\n");
	if (argc == 1)
		return (exit_prg(msh, msh->status));
	if (argc > 2)
	{
		print_error(ERARGC, "exit", NULL);
		return (1);
	}
	exstat = ft_atoll(argv[1]);
	if (argv[1] && (!only_digits(argv[1]) || exstat == -1))
	{
		print_error(ERNUMARG, "exit", argv[1]);
		exit_prg(msh, 2);
	}
	return (exit_prg(msh, (unsigned char)exstat));
}

long long	ft_atoll(char *s)
{
	int					i;
	int					sign;
	int					cutlim;
	unsigned long long	cutoff;
	unsigned long long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			sign = -sign;
	if (sign > 0)
		cutoff = LL_MAX;
	else
		cutoff = -(unsigned long long)LL_MIN;
	cutlim = (int)((cutoff) % 10);
	cutoff /= 10;
	while (ft_isdigit(s[i]))
	{
		if (res > cutoff || (res == cutoff && (s[i] - 48) > (int)cutlim))
			return (-1);
		res = res * 10 + (s[i++] - 48);
	}
	return ((long long)(res * sign));
}

int	only_digits(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '+' && s[0] != '-' && !ft_isdigit(s[0]))
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}
