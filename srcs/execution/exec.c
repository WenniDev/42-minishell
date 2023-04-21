//	NORM
//		-missing header

#include "spash.h"
#include "spash_parsing.h"
#include "spash_error.h"
#include "spash_exec.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

void	init_fds(t_data *data, int fds[4])
{
	fds[IN] = dup(STDIN_FILENO);
	fds[OUT] = dup(STDOUT_FILENO);
	if (fds[IN] == ERROR || fds[OUT] == ERROR)
	{
		sperr(data, NULL, "dup", errno);
		exit_prg(data);
	}
	if (pipe(&fds[PIPE0]) == ERROR)
	{
		sperr(data, NULL, "pipe", errno);
		exit_prg(data);
	}
}

void	reset_io(t_data *data)
{
	if (dup2(data->fds[IN], STDIN_FILENO) == ERROR
		|| dup2(data->fds[OUT], STDOUT_FILENO) == ERROR)
	{
		sperr(data, NULL, "dup2", errno);
		exit_prg(data);
	}
}

int	check_exec(t_data *data, int i, int *w_nb)
{
	int	stat;

	if (data->c_table[i].exec_if)
	{
		if (waitpid(data->c_table[i - 1].pid, &stat, 0) == ERROR)
			(sperr(data, NULL, "waitpid", errno), exit_prg(data));
		(*w_nb)--;
	}
	if ((data->c_table[i].exec_if == IF_TRUE && !WEXITSTATUS(stat))
		|| (data->c_table[i].exec_if == IF_FALSE && WEXITSTATUS(stat))
		|| data->c_table[i].exec_if == ALL)
		return (true);
	return (false);
}

int	wait_cmds(t_data *data, int w_nb)
{
	int i;
	int stat;

	i = 0;
	if (waitpid(data->c_table[data->c_nb - 1].pid, &stat, 0) == ERROR)
		(sperr(data, NULL, "waitpid", errno), exit_prg(data));
	while (i < w_nb - 1)
	{
		if (wait(NULL) == ERROR)
			(sperr(data, NULL, "wait", errno), exit_prg(data));
		i++;
	}
	data->exit_status = stat;
	return (stat);
}

int	exec(t_data *data)
{
	int		i;
	int		w_nb;
	bool	exec;

	i = 0;
	w_nb = data->c_nb;
	init_fds(data, data->fds);
	while (i < data->c_nb)
	{
		io_red(data, i);
		if (data->c_nb == 1 && data->c_table[0].type == BUILTIN)
			return (exec_builtin(data, data->c_table[0]));
		exec = check_exec(data, i, &w_nb);
		data->c_table[i].pid = fork();
		if (data->c_table[i].pid == ERROR)
			(sperr(data, NULL, "fork", errno), exit_prg(data));
		if (!data->c_table[i].pid)
			exec_cmd(data, data->c_table[i], exec);
		i++;
	}
	reset_io(data);
	return (wait_cmds(data, w_nb));
}
