//	NORM
//		-missing header

#include "libft.h"

char	*ft_strstr(const char *big, const char *small)
{
	int		i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(small);
	if (!big || !small || !*small)
		return (NULL);
	while (big[i])
	{
		if (!ft_strncmp(big + i, small, slen))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
