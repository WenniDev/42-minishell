/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirect.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:39:47 by rsabbah           #+#    #+#             */
/*   Updated: 2023/05/27 10:39:48 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_REDIRECT_H
# define MINISHELL_REDIRECT_H

# include <stdbool.h>

# define CLOSE	1
# define DUP	2
# define DUP2	3
# define PIPE	4

void	close_all(t_exec *e);
int		do_redir(int status, t_exec *e, t_command cmd);
void	set_fds(t_exec *e, int flag);
void	do_ft(int ft, int *ft_data1, int ft_data2);
int		here_document_to_fd(t_red *hd, int status);

#endif