/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:04:27 by jopadova          #+#    #+#             */
/*   Updated: 2023/05/28 20:12:25 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_command.h"
#include "minishell_expand.h"
#include "minishell_error.h"

int			get_wnb(char *s, char *sep);
int			get_wlen(char *s, char *sep);
t_word_lst	*new_elem(char *s);

void	word_splitting(t_word_d *w, t_word_lst **wl, int *status)
{
	int			wnb;
	int			i;
	t_word_lst	*elem;
	t_word_lst	*tmp;

	(void)status;
	i = 0;
	tmp = NULL;
	if (!getenv("IFS"))
		return ;
	wnb = get_wnb(w->lval, getenv("IFS"));
	while (i < wnb)
	{
		elem = new_elem(w->lval);
		add_in_list(&tmp, elem);
		i++;
	}
	insert_list(w, wl, &tmp);
}

t_word_lst	*new_elem(char *s)
{
	t_word_lst	*elem;
	t_word_d	*new_w;
	static int	i;
	int			wlen;

	while (ft_strchr(getenv("IFS"), s[i]))
		i++;
	elem = (t_word_lst *)sfcalloc(1, sizeof (t_word_lst));
	new_w = (t_word_d *)sfcalloc(1, sizeof (t_word_d));
	elem->word = new_w;
	wlen = get_wlen(s + i, getenv("IFS"));
	new_w->lval = ft_substr(s + i, 0, wlen);
	if (!new_w->lval)
		malloc_error();
	i += wlen;
	if (!s[i])
		i = 0;
	return (elem);
}

int	get_wlen(char *s, char *sep)
{
	int	len;

	len = 0;
	while (s[len] && (!ft_strchr(sep, s[len]) || s[len] == '"'))
	{
		if (s[len] == '"')
		{
			len++;
			while (s[len] != '"')
				len++;
		}
		len++;
	}
	return (len);
}

int	get_wnb(char *s, char *sep)
{
	int	i;
	int	wnb;

	wnb = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_strchr(sep, s[i]))
		{
			wnb++;
			while (s[i] && (!ft_strchr(sep, s[i]) || s[i] == '"'))
			{
				if (s [i] && s[i] == '"')
				{
					i++;
					while (s[i] && s[i] != '"')
						i++;
				}
				i++;
			}
		}
		else
			i++;
	}
	return (wnb);
}
