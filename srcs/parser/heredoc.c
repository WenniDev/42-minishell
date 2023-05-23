/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:27:48 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/23 19:11:52 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"
#include "minishell_expand.h"

#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int ft_random()
{
	unsigned char	buffer[3];
	int				ran_int;
	ssize_t			bytes_read;
	int 			fd;

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
	if (r->filename->flags & W_NOEXPAND)
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

int print_eof_error(char *eof)
{
	ft_putstr_fd("msh: ", 2);
	ft_putstr_fd(HDERREOF, 2);
	ft_putstr_fd(" (wanted \"", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("\")\n", 2);
	return (-1);
}

char	*read_heredoc(t_parser *p, t_red *r)
{
	char	*line;
	char	*res;
	int		len;
	int 	index;

	index = 0;
	res = NULL;
	while (true)
	{
		line = get_line(p);
		if (!line)
		{
			print_eof_error(r->heredoc_eof);
			break;
		}
		if (!ft_strcmp(line, r->heredoc_eof))
			break;
		len = (int)ft_strlen(line);
		if (res)
			res = ft_realloc(res, ft_strlen(res) + len + 2, ft_strlen(res));
		else
			res = ft_realloc(res, len + 2, 0);
		ft_memcpy(res + index++, line, len);
		ft_memcpy(res + ft_strlen(res), "\n", 1);
		index += len;
	}
	return (free(r->filename->lval), res);
}

void	gather_heredoc(t_parser *p)
{
	t_red *hd;

	hd = p->hd_lst;
	p->state |= PST_HEREDOC;
	while (hd)
	{
		if (ft_strchr(hd->heredoc_eof, '\''))
		{
			hd->filename->flags |= W_NOEXPAND;
			skip_quotes(hd->heredoc_eof);
		}
		hd->filename->lval = read_heredoc(p, hd);
		hd = hd->next;
	}
	p->state &= ~PST_HEREDOC;
}

int create_tmp(char *content, t_red *r)
{
	char			*ran_char;
	char 			*filename;
	int 			fd;

	ran_char = ft_itoa(ft_random());
	filename = ft_strjoin("/tmp/sh-thd-", ran_char);
	free(ran_char);
	fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0664);
	if (fd == -1)
		return (-1);
	if (write(fd, content, ft_strlen(content)) < 0)
		return (-1);
	if (close(fd))
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	unlink(filename);
	r->filename->lval = filename;
	return (fd);
}

int	heredoc(t_red *r)
{
	char	*document;
	int 	document_len;
	int 	fd;

	document = heredoc_expand(r, &document_len);
	if (document_len == 0)
	{
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
			return (0);
		return (fd);
	}
	fd = create_tmp(document, r);
	free(document);
	return (fd);
}