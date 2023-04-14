/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:59:29 by rsabbah           #+#    #+#             */
/*   Updated: 2023/04/14 18:59:43 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spash.h"
#include "libft.h"

void	init_grammar(t_data *data, char **grammar)
{
	grammar = (char **)ft_calloc(9, sizeof (char *));
}

void	init(t_data *data)
{
	if (data)
	{
		ft_memset(data, 0, sizeof (t_data));
		init_grammar(data, data->syntax.grammar);
		data->cmd_line = EMPTY;
	}
}
