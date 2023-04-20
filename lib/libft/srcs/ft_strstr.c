//	NORM
//		-missing header

#include "libft.h"

char	*ft_strstr(const char *big, const char *small)
{
	int		i;

	i = 0;
	if (!big || !small || !*small)
		return (NULL);
	while (big[i] && small[i])
	{
		if (!ft_strcmp(big + i, small))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
