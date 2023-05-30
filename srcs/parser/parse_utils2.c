/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:54:28 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:54:42 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"

static const char	*g_builtins[7] = {
	"pwd", "echo", "exit", "env", "unset", "export", "cd"
};

t_red	*ft_last_red(t_red *r)
{
	if (!r)
		return (NULL);
	if (!r->next)
		return (r);
	return (ft_last_red(r->next));
}

int	ft_is_builtin(char *s)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(s, g_builtins[i]))
			return (1);
		i++;
	}
	return (0);
}

int	end_subshell_cmd(t_parser *p)
{
	t_addr_lst	*tmp;

	if (p->sub_lst)
	{
		p->cl_curr = p->sub_lst->addr;
		tmp = p->sub_lst->prev;
		ft_free((void **) &p->sub_lst);
		p->sub_lst = tmp;
		return (1);
	}
	return (0);
}
