/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:13:25 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/27 10:50:26 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_command.h"
#include "minishell_expand.h"

char	*here_document_expand(int ls, t_red *r, int *len)
{
	int			status;
	t_word_d	tmp;

	status = 0;
	tmp.lval = r->hd_content;
	tmp.flags = r->filename->flags;
	if (r->hd_content == 0 || r->hd_content[0] == '\0')
	{
		if (len)
			*len = 0;
		return (r->hd_content);
	}
	if (r->filename->flags & W_NOEXPAND)
	{
		if (len)
			*len = (int)ft_strlen(r->hd_content);
		return (r->hd_content);
	}
	expand_env(&tmp, &status, ls);
	r->hd_content = tmp.lval;
	if (len)
		*len = (int)ft_strlen(r->hd_content);
	return (r->hd_content);
}
