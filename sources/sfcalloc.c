#include <stdlib.h>
#include <signal.h>
#include "libft.h"

void	*sfcalloc(size_t n, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = n * size;
	if (n == 0 || size == 0)
		ptr = malloc(1);
	else
		ptr = malloc(total_size);
	if (!ptr)
	{
		ft_putstr_fd("Malloc failed", 2);
		kill(0, SIGABRT);
	}
	ft_memset(ptr, 0, total_size);
	return (ptr);
}
