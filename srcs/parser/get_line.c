#include "minishell_parse.h"

char	*add_line(char *cmd_line, char *line, t_bool space);

char	*get_line(t_parser *p)
{
	if (p->line_read)
		ft_free((void **)&p->line_read);
	if (p->state & PST_SUBSHELL)
		p->line_read = readline("subcmd> ");
	else if (p->state & PST_HEREDOC)
		p->line_read = readline("heredoc> ");
	else
		p->line_read = readline(getenv("PS1"));
	if (!p->line_read)
	{
		if (p->state & PST_SUBSHELL)
		{
			p->status = EXS_SYNTAX_ERROR;
			syntax_error(EREOF, 0, NULL);
		}
		return (NULL);
	}
	(p->line)++;
	if (*p->line_read)
		p->cmd_line = add_line(p->cmd_line, p->line_read, p->state & PST_HEREDOC);
	p->line_ptr = p->line_read;
	return (p->line_read);
}

/* add the new line to the full command line for later add to history */
char	*add_line(char *cmd_line, char *line, t_bool nl)
{
	char	*tmp;
	size_t	len;
	size_t	size;

	tmp = cmd_line;
	len = ft_strlen(cmd_line);
	size = len + ft_strlen(line) + 1 + (len > 0) + nl;
	cmd_line = (char *)sfcalloc(size, sizeof (char));
	ft_strlcpy(cmd_line, tmp, size);
	if (len && nl)
		cmd_line[len] = NEWLINE;
	else if (len)
		cmd_line[len] = SPACE;
	ft_strlcat(cmd_line, line, size);
	ft_free((void **)&	tmp);
	return (cmd_line);
}