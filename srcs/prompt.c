/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:00:41 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 11:00:47 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_builtins.h"

char	*join_prompt(char *user, char *dir);
char	*get_dir(void);

void	set_prompt(t_data *msh)
{
	char	*prompt;
	char	*user;
	char	*dir;
	char	*tmp;

	export_var("PS1", "$> ", &msh->exec);
	if (!getenv("USER"))
		return ;
	prompt = NULL;
	dir = get_dir();
	user = getenv("USER");
	prompt = join_prompt(user, dir);
	tmp = prompt;
	if (msh->status)
		prompt = ft_strjoin(prompt, "\e[1;30m$\e[31m> \e[0m");
	else
		prompt = ft_strjoin(prompt, "\e[1;30m$\e[32m> \e[0m");
	free(tmp);
	if (!prompt)
		malloc_error();
	export_var("PS1", prompt, &msh->exec);
	free(prompt);
}

char	*join_prompt(char *user, char *dir)
{
	char	*prompt;
	char	*tmp;

	prompt = ft_strjoin(user, ":");
	if (!prompt)
		malloc_error();
	tmp = prompt;
	prompt = ft_strjoin(prompt, dir);
	free(dir);
	free(tmp);
	if (!prompt)
		malloc_error();
	tmp = prompt;
	prompt = ft_strjoin("\e[1;30m", prompt);
	free(tmp);
	if (!prompt)
		malloc_error();
	return (prompt);
}

char	*get_dir(void)
{
	char	*dir;
	char	*ptr;
	char	*tmp;
	size_t	len;

	dir = getenv("PWD");
	if (!dir)
		return (NULL);
	len = ft_strlen(dir);
	ptr = dir + len;
	while (*ptr != '/')
		ptr--;
	len = (dir + len) - ptr;
	dir = ft_substr(dir, ptr - dir, len);
	if (!dir)
		malloc_error();
	tmp = dir;
	dir = ft_strjoin("\e[1;34m", dir);
	free(tmp);
	if (!dir)
		malloc_error();
	return (dir);
}
