/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:23:45 by yonadry           #+#    #+#             */
/*   Updated: 2024/01/07 18:24:00 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (str[i] && str[i] != '\n')
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	ft_issame(char find, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == find)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	if (s1 == 0)
		return (NULL);
	if (set == 0)
		return ((char *)s1);
	j = ft_strlen((char *)s1) - 1;
	while (s1[i] != '\0' && ft_issame((char)s1[i], (char *)set))
		i++;
	while (j >= 0 && ft_issame((char)s1[j], (char *)set))
		j--;
	if (j == -1)
		return (ft_substr(s1, i, 0));
	return (ft_substr(s1, i, j - i + 1));
}
