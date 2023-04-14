/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spash.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:17:36 by rsabbah           #+#    #+#             */
/*   Updated: 2023/04/14 18:55:07 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPASH_H
# define SPASH_H

# include <stddef.h>

typedef struct s_data
{
	char			*cmd_line;
	t_simple_cmd	*simple_cmds;
	int				simple_cmd_nb;
	t_syntax		syntax;
}t_data;

#endif
