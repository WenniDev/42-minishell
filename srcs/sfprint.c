/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sfprint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:51:19 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/31 13:06:01 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_utils.h"
#include "minishell_error.h"
#include "minishell.h"

int	sfprint(char *s, bool newline)
{
	if (!s)
		return (0);
	if (write(STDOUT_FILENO, s, ft_strlen(s)) == -1)
		return (-1);
	if (newline)
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (-1);
	return (0);
}
