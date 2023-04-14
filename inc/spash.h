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
	t_cmd		cmd;
	t_syntax	syntax;
	t_error		error;
	int			exit_status;
}t_data;

#endif
