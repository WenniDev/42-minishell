/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <jopadova@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:26:40 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/19 01:16:42 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parse.h"
#include "minishell_expand.h"

int is_expandable(char *str)
{
	while (str && *str != '\'')
		str++;
	if (!str)
		return (0);
	while (str && *str != '\'')
		str++;
	if (!str)
		return (0);
	return (1);
}

char *heredoc_expand(t_red *r, int *len)
{
	int status;

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

int	heredoc(t_red *r)
{
	char	*document;
	int 	document_len;
	int 	fd;

	(void) document;
	document = heredoc_expand(r, &document_len);
	if (document_len == 0)
	{
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
			return (0);
		return (fd);
	}
	return (0);
}
