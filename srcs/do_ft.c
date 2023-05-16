#include"minishell.h"

void	do_ft(int ft, int *ft_data1, int ft_data2)
{
	if (ft == CLOSE)
	{
		if (*ft_data1 && close(*ft_data1) == -1)
			msh_error(ERCLOSE);
		*ft_data1 = 0;
	}
	if (ft == DUP)
	{
		*ft_data1 = dup(ft_data2);
		if (*ft_data1 == -1)
			msh_error(ERDUP);
	}
	if (ft == DUP2)
	{
		if (dup2(*ft_data1, ft_data2) == -1)
			msh_error(ERDUP2);
	}
	if (ft == PIPE)
	{
		if (pipe(ft_data1) == -1)
			msh_error(ERPIPE);
	}
}
