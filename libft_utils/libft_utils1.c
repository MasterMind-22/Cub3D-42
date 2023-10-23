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

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}