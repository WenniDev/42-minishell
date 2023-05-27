/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:39:55 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:39:56 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

void	*sfcalloc(size_t n, size_t size);
int		sfprint(char *s, bool newline);

#endif
