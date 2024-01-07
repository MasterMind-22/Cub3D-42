/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:25:38 by yonadry           #+#    #+#             */
/*   Updated: 2024/01/07 18:26:00 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	newline_found(char *read_line)
{
	int	i;

	i = 0;
	if (!read_line)
		return (1);
	while (read_line[i] != '\0')
	{
		if (read_line[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*copy;
	size_t	len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	copy = malloc(len + 1);
	if (!copy)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*str1;
	char	*str2;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (!s2)
		return (NULL);
	str1 = (char *)s1;
	if (!str1)
		str1 = ft_calloc(1, 1);
	str2 = (char *)s2;
	res = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!res)
		return (NULL);
	while (str1[++i])
		res[i] = str1[i];
	res[i] = '\0';
	while (str2[++j])
		res[i++] = str2[j];
	res[i] = '\0';
	free(str1);
	return (res);
}
