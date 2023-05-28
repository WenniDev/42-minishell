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

static void	clean_elems(t_word_lst *words)
{
	void	*tmp;

	while (words)
	{
		tmp = words->next;
		ft_free((void **) &words->word->lval);
		ft_free((void **) &words->word);
		ft_free((void **) &words);
		words = (t_word_lst *) tmp;
	}
}

static int	add_word(t_word_lst **word_lst, char *lval)
{
	t_word_lst	*new_file;

	new_file = ft_calloc(1, sizeof(t_word_lst));
	if (!new_file)
		return (0);
	new_file->word = ft_calloc(1, sizeof(t_word_d));
	if (!new_file->word)
		return (0);
	new_file->word->lval = lval;
	if (!new_file->word->lval)
		return (0);
	new_file->word->flags = 0;
	new_file->next = NULL;
	add_in_list(word_lst, new_file);
	return (1);
}

char	*ft_strpbrk(char *str1, char *str2)
{
	char	*p_str1;
	char	*p_str2;

	p_str1 = str1;
	while (*p_str1 != '\0')
	{
		p_str2 = str2;
		while (*p_str2 != '\0')
		{
			if (*p_str1 == *p_str2)
				return (p_str1);
			p_str2++;
		}
		p_str1++;
	}
	return (NULL);
}

void	word_splitting(t_word_d *word, t_word_lst **word_lst, int *status)
{
	t_word_lst	*tmp_lst;
	int			i;
	char		**splitted;

	if (!getenv("IFS"))
		return ;
	if (!ft_strpbrk(word->lval, getenv("IFS")))
		return ;
	tmp_lst = NULL;
	splitted = ft_split(word->lval, getenv("IFS"));
	if (!splitted)
		return (*status = 1, (void) NULL);
	i = 0;
	while (splitted[i])
		if (!add_word(&tmp_lst, splitted[i++]))
			return (*status = 1, free_word_lst(tmp_lst), clean_elems(tmp_lst));
	insert_list(word, word_lst, &tmp_lst);
	ft_free((void **) &splitted);
	*status = 0;
}
