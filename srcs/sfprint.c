#include "minishell_utils.h"

int	sfprint(char *s, bool newline)
{
	if (write(STDOUT_FILENO, s, ft_strlen(s)) == -1)
		return (-1);
	if (newline)
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (-1);
	return (0);
}
