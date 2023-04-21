/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:48:28 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/02 15:41:33 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dest2;
	char	*src2;

	if (dest == NULL || src == NULL)
		return (NULL);
	dest2 = (char *)dest;
	src2 = (char *)src;
	i = 0;
	while (i < n && dest2[i] && src2[i])
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest);
}
