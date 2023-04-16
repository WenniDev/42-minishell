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

# include "spash_types.h"
# include <stddef.h>

void	init(t_data *data);

void	sperr(t_data *data, char *msg, char *infos, int errnum);
void	put_sperr(t_error error);

int		exit_prg(t_data *data);

#endif
