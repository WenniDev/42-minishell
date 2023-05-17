#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

void	*sfcalloc(size_t n, size_t size);
int		sfprint(char *s, bool newline);

#endif
