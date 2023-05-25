#include "minishell_parse.h"
#include "minishell_expand.h"
#include "minishell.h"

int		here_document_read(t_parser *p, t_red *hd);
int 	here_document_warning(t_parser *p, char *eof);
void	add_content(char **s, char *content);

void	gather_heredoc(t_parser *p)
{
	t_red 	*hd;
	int		tmpin;

	do_ft(DUP, &tmpin, STDIN_FILENO);
	hd = p->hd_lst;
	p->state |= PST_HEREDOC;
	while (hd && hd->rflags & RED_HEREDOC && p->state & PST_HEREDOC)
	{
		if (ft_strchr(hd->heredoc_eof, '\''))
		{
			hd->filename->flags |= W_NOEXPAND;
			skip_quotes(hd->heredoc_eof);
		}
		if (here_document_read(p, hd) == -1)
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
		add_content(&hd->filename->lval, line);
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