#include "../cub3d.h"

char	*ft_strstr(const char *str, const char *sub)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str)
		return (NULL);
	if (*sub == '\0')
		return ((char *)str);
	while (str[i])
	{
		j = 0;
		while (str[i + j] == sub[j] && sub[j])
		{
			if (sub[j + 1] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}