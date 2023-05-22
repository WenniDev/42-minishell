/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:26:40 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/20 00:18:59 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"
#include "minishell_expand.h"

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int ft_random() {
	unsigned char	buffer[3];
	int				randomInt;
	ssize_t			bytesRead;
	int 			fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (-1);
	bytesRead = read(fd, buffer, 3);
	if (bytesRead != 3)
		return (-1);
	close(fd);
	randomInt = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
	return (randomInt);
}

int is_expandable(char *str)
{
	while (str && *str && *str != '\'')
		str++;
	if (!str || !(*str))
		return (0);
	while (str && *str && *str != '\'')
		str++;
	if (!str || !(*str))
		return (0);
	return (1);
}

char *heredoc_expand(t_red *r, int *len)
{
	int status;

	status = 0;
	if (r->filename->lval == 0 || r->filename->lval[0] == '\0')
	{
		if (len)
			*len = 0;
		return (r->filename->lval);
	}
	if (r->heredoc_eof && is_expandable(r->heredoc_eof))
	{
		if (len)
			*len = (int)ft_strlen(r->filename->lval);
		return (r->filename->lval);
	}
	expand_env(r->filename, &status);
	if (len)
		*len = (int)ft_strlen(r->filename->lval);
	return (r->filename->lval);
}

int read_heredoc(t_parser *p, t_red *r)
{
	char *tmp;

	while (1)
	{
		tmp = get_line(p);
		if (!ft_strcmp(tmp, r->heredoc_eof))
			break ;
		r->filename->lval = ft_strjoin(r->filename->lval, "\n");
		if (!r->filename->lval)
			return (1);
		r->filename->lval = ft_strjoin(r->filename->lval, tmp);
		if (!r->filename->lval)
			return (1);
		free(tmp);
	}
	return (0);
}

int create_tmp(char *content)
{
	char			*ran_char;
	char 			*filename;
	int 			fd;

	ran_char = ft_itoa(ft_random());
	filename = ft_strjoin("/tmp/sh-thd-", ran_char);
	free(ran_char);
	fd = open(filename, O_CREAT | O_TRUNC | O_EXCL | O_WRONLY);
	if (fd == -1)
		return (-1);
	write(fd, content, ft_strlen(content));
	if (close(fd))
		return (-1);
	fd = open(filename, O_RDONLY);
	return (fd);
}

int	get_heredoc(t_parser *p, t_red *r)
{
	char	*document;
	int 	document_len;
	int 	fd;

	p->state = PST_HEREDOC;
	if (read_heredoc(p, r) == 1)
		return (1);
	document = heredoc_expand(r, &document_len);
	if (document_len == 0)
	{
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
			return (0);
		return (fd);
	}
	fd = create_tmp(document);
	return (fd);
}
