/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 05:57:28 by yonadry           #+#    #+#             */
/*   Updated: 2024/03/23 05:57:29 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	is_that_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != ' '
			&& str[i] != 'E' && str[i] != 'W' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	deci_to_hexa_color(int red, int green, int blue)
{
	int	rgb;

	rgb = (red << 16) | (green << 8) | blue;
	return (rgb);
}

char	*check_extension(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (ft_strncmp(".cub", av + (ft_strlen(av) - 4), 4) || fd == -1)
	{
		close(fd);
		p_error("Invalid Extension");
	}
	close(fd);
	return (av);
}

int	count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	file_col_num(t_cub3d *cub3d)
{
	int		count;
	char	*str;
	int		fd;

	count = 1;
	fd = open(cub3d->file_name, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		count++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (count);
}
