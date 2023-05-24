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

#include "minishell.h"
#include "minishell_parse.h"
#include "minishell_expand.h"
#include "minishell_redirect.h"

#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	read_heredoc(t_data *msh, t_parser *p, t_red *hd);
char	*get_content(t_parser *p, t_red *hd);
char	*read_from_heredoc(int fd);
void	handle_sig(int signum);

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

char *heredoc_expand(int ls, t_red *r, int *len)
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
	expand_env(r->filename, &status, ls);
	if (len)
		*len = (int)ft_strlen(r->filename->lval);
	return (r->filename->lval);
}

int print_eof_error(t_parser *p, char *eof)
{
	char	*line;

	line = ft_itoa(p->line);
	ft_putstr_fd("msh: ", 2);
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putstr_fd(line, 2);
	free(line);
	ft_putstr_fd(" delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted \"", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("\")\n", 2);
	return (-1);
}


void	gather_heredoc(t_data *msh, t_parser *p)
{
	t_red *hd;

	hd = p->hd_lst;
	p->state |= PST_HEREDOC;
	while (hd && p->state & PST_HEREDOC)
	{
		if (ft_strchr(hd->heredoc_eof, '\''))
		{
			hd->filename->flags |= W_NOEXPAND;
			skip_quotes(hd->heredoc_eof);
		}
		if (read_heredoc(msh, p, hd) == -1)
			break ;
		hd = hd->next;
	}
	p->state &= ~PST_HEREDOC;
}

int create_tmp(t_red *r)
{
	char			*ran_char;
	int 			fd;

	ran_char = ft_itoa(ft_random());
	ft_free((void **)&r->filename->lval);
	if (!ran_char)
		malloc_error();
	r->filename->lval = ft_strjoin("/tmp/sh-thd-", ran_char);
	free(ran_char);
	if (!r->filename->lval)
		malloc_error();
	fd = open(r->filename->lval, O_CREAT | O_EXCL | O_RDWR, 0664);
	if (!r->filename->lval)
		malloc_error();
	if (fd == -1)
		return (print_error(strerror(errno), r->filename->lval, NULL));
	return (fd);
}

int heredoc_to_fd(char *content, t_red *r)
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

int	heredoc(t_red *r, int ls)
{
	char	*document;
	int 	document_len;
	int 	fd;

	document = heredoc_expand(ls, r, &document_len);
	if (document_len == 0)
	{
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
			return (0);
		return (fd);
	}
	fd = heredoc_to_fd(document, r);
	free(document);
	return (fd);
}

int	read_heredoc(t_data *msh, t_parser *p, t_red *hd)
{
	int		fd;
	int		status;
	char	*content;
	pid_t	pid;

	fd = create_tmp(hd);
	if (fd == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		msh_error(ERFORK);
	if (!pid)
	{
		msh->exec.child = true;
		content = get_content(p, hd);
		write(fd, content, ft_strlen(content));
		free(content);
		do_ft(CLOSE, &fd, 0);
		exit_prg(msh, 0);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			msh_error(ERWAITPID);
		close(fd);
		open(hd->filename->lval, O_RDONLY);
		content = read_from_heredoc(fd);
		unlink(hd->filename->lval);
		free(hd->filename->lval);
		hd->filename->lval = content;
		if (WEXITSTATUS(status) == SIGTERM)
			return (reset_parser(p), -1);
	}
	return (0);
}

char	*get_content(t_parser *p, t_red *hd)
{
	char	*line;
	char	*content;
	char	*tmp;
	size_t	size;

	content = NULL;
	while (true)
	{
		line = get_line(p);
		if (!(p->state & PST_HEREDOC))
			break ;
		if (!line)
			return (print_eof_error(p, hd->heredoc_eof), content);
		if (!ft_strcmp(line, hd->heredoc_eof))
			break ;
		tmp = content;
		size = ft_strlen(tmp) + ft_strlen(line) + 2;
		content = (char *)sfcalloc(size, 1);
		ft_strlcpy(content, tmp, size);
		ft_strlcat(content, line, size);
		ft_strlcat(content, "\n", size);
		if (tmp)
			free(tmp);
	}
	return (content);
}

char	*read_from_heredoc(int fd)
{
	char	*content;
	char	*buffer[1024];
	char	*tmp;
	size_t	size;
	int		n;

	n = 1;
	content = NULL;
	while (n)
	{
		n = (int)read(fd, buffer, 1024);
		if (n == -1)
			msh_error(ERREAD);
		tmp = content;
		size = ft_strlen(tmp) + n + 1;
		content = (char *)sfcalloc(size, 1);
		ft_strlcpy(content, tmp, size);
		ft_strlcat(content, (char *)buffer, size);
		if (tmp)
			free(tmp);
	}
	return (content);
}
