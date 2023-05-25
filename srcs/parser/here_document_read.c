/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document_read.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:06:49 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/25 19:10:49 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"
#include "minishell_expand.h"
#include "minishell.h"

int		here_document_read(t_parser *p, t_red *hd);
int 	here_document_warning(t_parser *p, char *eof);
void	add_content(char **s, char *content);

void	gather_heredoc(t_parser *p)
{
	t_hd 	*hd;
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
	char	*line;

	line = NULL;
	while (ft_strcmp(line, hd->heredoc_eof))
	{
		add_content(&hd->hd_content, line);
		line = get_line(p);
		if (!(p->state & PST_HEREDOC))
			return (-1);
		if (!line)
			return (here_document_warning(p, hd->heredoc_eof));
	}
	return (0);
}

void	add_content(char **s, char *content)
{
	char	*tmp;
	size_t	size;

	if (!content)
		return ;
	tmp = *s;
	size = ft_strlen(tmp) + ft_strlen(content) + 2;
	*s = (char *)sfcalloc(size, sizeof (char));
	ft_strlcpy(*s, tmp, size);
	ft_strlcat(*s, content, size);
	ft_strlcat(*s, "\n", size);
	ft_free((void **)&tmp);
}

int here_document_warning(t_parser *p, char *eof)
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
	return (0);
}