//	NORM
//		-missing header

#include "spash.h"
#include "spash_parsing.h"
#include "spash_error.h"
#include "spash_exec.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void	init_io_red(t_data *data, int i, int io_fd[2])
{
	io_fd[IN] = 0;
	io_fd[OUT] = 0;
	if (!i || data->c_table[i].exec_if)
		io_fd[IN] = dup(data->fds[IN]);
	if (i == data->c_nb - 1 || data->c_table[i].exec_if)
		io_fd[OUT] = dup(data->fds[OUT]);
	if (i && data->c_table[i].exec_if == ALL)
		io_fd[IN] = data->fds[PIPE0];
	if (i != data->c_nb - 1 && data->c_table[i].exec_if == ALL)
		io_fd[OUT] = data->fds[PIPE1];
}

void	manage_io_red(t_data *data, t_red *red, int io_fd[2])
{
	if (red->op == IN_RED)
		io_fd[IN] = open(red->file, O_RDONLY);
	else if (red->op == HEREDOC_RED)
		io_fd[IN] = heredoc(data, red->file);
	if (red->op == OUTTR_RED || red->op == OUTAP_RED)
		io_fd[OUT] = open(red->file, red->flags);
	if (io_fd[IN] == ERROR || io_fd[OUT] == ERROR)
	{
		sperr(data, NULL, red->file, errno);
		exit_prg(data);
	}
	if (red->next && io_fd[OUT] != data->fds[OUT])
		close(io_fd[OUT]);
}

void	io_red(t_data *data, int i)
{
	t_red	*red;
	int		io_fd[2];

	init_io_red(data, i, io_fd);
	while (red)
	{
		manage_io_red(data, red, io_fd);
		red = red->next;
	}
	if (dup2(io_fd[IN], STDIN_FILENO) == ERROR
		|| dup2(io_fd[OUT], STDOUT_FILENO) == ERROR)
	{
		close(io_fd[IN]);
		close(io_fd[OUT]);
		sperr(data, NULL, "dup2", errno);
		exit_prg(data);
	}
	close(io_fd[IN]);
	close(io_fd[OUT]);
}
