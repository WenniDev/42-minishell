/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:45:18 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:45:29 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

char	*get_binary(char **paths, char *cmd_name)
{
	int		i;
	char	*tmp;
	char	*bin;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			(free_split(paths), malloc_error());
		bin = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (!bin)
			(free_split(paths), malloc_error());
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		i++;
	}
	return (NULL);
}

char	*get_path(t_data *msh, char *cmd_name)
{
	char	**paths;
	char	*bin;
	bool	pth;

	pth = (*cmd_name == '.' || *cmd_name == '/' || *cmd_name == '~');
	if (!getenv("PATH"))
		(print_error(strerror(2), cmd_name, NULL), exit_prg(msh, 127));
	paths = ft_split(getenv("PATH"), ":");
	if (!paths)
		malloc_error();
	if (pth)
		bin = ft_strdup(cmd_name);
	else
		bin = get_binary(paths, cmd_name);
	free_split(paths);
	if (!bin)
		(print_error(CMDNOTF, cmd_name, NULL), exit_prg(msh, 127));
	if (pth && access(bin, X_OK) == EXS_ERROR)
		(print_error(strerror(errno), cmd_name, NULL), exit_prg(msh, 127));
	if (access(bin, X_OK) == EXS_ERROR)
		(free (bin), print_error(CMDPERMD, cmd_name, NULL), exit_prg(msh, 126));
	return (bin);
}
