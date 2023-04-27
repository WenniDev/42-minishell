/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopadova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:17:16 by jopadova          #+#    #+#             */
/*   Updated: 2023/04/27 15:14:22 by jopadova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spash.h"
#include "spash_parsing.h"
#include "spash_error.h"
#include "spash_exec.h"
#include <fcntl.h>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>

# define HEREDOC_TMP	"/tmp/heredoc_minishell"

/* 
	strace -o steps_out -ff -e open,close,unlink,read,write,execve,readline,dup2 -- $sh ./test.sh

	test.sh:

		#!/bin/sh
		for i in $(seq 10); do
		cat <<EOF
		here doc $i
		EOF
		done
*/

static int	create_heredoc(t_data *data)
{
	int	fd;

	fd = open(HEREDOC_TMP, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd < 0)
		(sperr(data, NULL, "heredoc", errno), exit_prg(data));
	return (fd);	
}

int heredoc(t_data *data, char *file)
{
	int fd;
	int	pid;
	int	tube[2];

	fd = create_heredoc(data);
	write_heredoc(fd);

	
	return(fd);
}
