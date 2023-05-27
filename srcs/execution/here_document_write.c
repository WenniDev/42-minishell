/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document_write.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:44:21 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:45:10 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execute.h"
#include "minishell_error.h"
#include "minishell_expand.h"
#include "minishell_redirect.h"

int	create_tmp(t_red *r);
int	ft_random(void);

int	here_document_to_fd(t_red *hd, int status)
{
	int	document_len;
	int	fd;

	here_document_expand(status, hd, &document_len);
	if (document_len == 0)
	{
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
			return (0);
		return (fd);
	}
	fd = create_tmp(hd);
	write(fd, hd->hd_content, ft_strlen(hd->hd_content));
	do_ft(CLOSE, &fd, 0);
	fd = open(hd->filename->lval, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	create_tmp(t_red *r)
{
	char	*ran_char;
	int		fd;

	ran_char = ft_itoa(ft_random());
	if (!ran_char)
		malloc_error();
	ft_free((void **)&r->filename->lval);
	r->filename->lval = ft_strjoin("/tmp/sh-thd-", ran_char);
	free(ran_char);
	if (!r->filename->lval)
		malloc_error();
	fd = open(r->filename->lval, O_CREAT | O_EXCL | O_RDWR, 0664);
	if (fd == -1)
		return (print_error(strerror(errno), r->filename->lval, NULL));
	return (fd);
}

int	ft_random(void)
{
	unsigned char	buffer[3];
	int				ran_int;
	ssize_t			bytes_read;
	int				fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (-1);
	bytes_read = read(fd, buffer, 3);
	if (bytes_read != 3)
		return (-1);
	close(fd);
	ran_int = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
	return (ran_int);
}
