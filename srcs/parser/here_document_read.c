/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document_read.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:06:49 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/27 10:53:11 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"
#include "minishell_expand.h"
#include "minishell.h"

int		here_document_read(t_parser *p, t_red *hd);
int		here_document_warning(t_parser *p, char *eof);
void	add_content(char **s, char *content);
void	remove_newline(char *s);

void	gather_heredoc(t_parser *p)
{
	t_hd	*hd;
	int		tmpin;

	do_ft(DUP, &tmpin, STDIN_FILENO);
	hd = p->hd_lst;
	p->state |= PST_HEREDOC;
	while (hd && p->state & PST_HEREDOC)
	{
		if (hd->red->filename->flags & W_QUOTES)
		{
			hd->red->filename->flags |= W_NOEXPAND;
			skip_quotes(hd->red->heredoc_eof);
		}
		else
			hd->red->filename->flags |= W_IGNORE;
		if (here_document_read(p, hd->red) == -1)
			break ;
		hd = hd->next;
	}
	do_ft(DUP2, &tmpin, STDIN_FILENO);
	do_ft(CLOSE, &tmpin, 0);
	p->state &= ~PST_HEREDOC;
}

int	here_document_read(t_parser *p, t_red *hd)
{
	char	buffer[1024];
	int		n;

	ft_memset((void *)buffer, 0, 1024);
	while (true)
	{
		ft_putstr_fd("heredoc> ", 1);
		ft_memset((void *)buffer, 0, 1024);
		n = (int)read(0, buffer, 1024);
		if (n == -1)
			return (p->status = 130, -1);
		if (!n)
			return (here_document_warning(p, hd->heredoc_eof));
		p->line++;
		remove_newline((char *)buffer);
		if (!ft_strcmp((char *)buffer, hd->heredoc_eof))
			return (0);
		add_content(&hd->hd_content, (char *)buffer);
	}
}

void	add_content(char **s, char *content)
{
	char	*tmp;
	size_t	size;

	if (!content || !(*content))
		return ;
	tmp = *s;
	size = ft_strlen(tmp) + ft_strlen(content) + 2;
	*s = (char *)sfcalloc(size, sizeof (char));
	ft_strlcpy(*s, tmp, size);
	ft_strlcat(*s, content, size);
	ft_strlcat(*s, "\n", size);
	ft_free((void **)&tmp);
}

int	here_document_warning(t_parser *p, char *eof)
{
	char	*line;

	line = ft_itoa(p->line);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("msh: ", 2);
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putstr_fd(line, 2);
	free(line);
	ft_putstr_fd(" delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted \"", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("\")\n", 2);
	return (0);
}

void	remove_newline(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	if (s && s[i])
		s[i] = '\0';
}
