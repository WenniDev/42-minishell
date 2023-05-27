/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sfcalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:00:53 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 11:00:54 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"
#include <stdlib.h>
#include <signal.h>
#include "libft.h"

void	*sfcalloc(size_t n, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = n * size;
	if (n == 0 || size == 0)
		ptr = malloc(1);
	else
		ptr = malloc(total_size);
	if (!ptr)
		msh_error(EMFAILED);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}
