//	NORM
//		-missing header

#include "spash_types.h"
#include "readline/readline.h"
#include "libft.h"

# define QUITMSG	"Quit"

t_data	*g_data;

void	handle_sig(int signum)
{
	int	i;

	i = 0;
	if (g_data->c_nb)
	{
		if (signum == SIGQUIT)
			ft_printf("%s", QUITMSG);
		ft_printf("\n");
		while (i < g_data->c_nb)
		{
			kill(g_data->c_table[i].pid, signum);
			i++;
		}
	}
	else if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		ft_printf("\r\e[K");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig(t_data *data)
{
	g_data = data;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
}
