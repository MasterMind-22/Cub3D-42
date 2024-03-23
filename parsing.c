/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:26:34 by yonadry           #+#    #+#             */
/*   Updated: 2024/03/23 06:44:21 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	parse_map(t_cub3d *cub3d)
{
	size_t	i;
	size_t	j;

	i = 0;
	more_checks(cub3d);
	while (i < cub3d->map_length)
	{
		j = 0;
		while (j < ft_strlen(cub3d->map[i]))
		{
			if (cub3d->map[i][j] == '0' || cub3d->map[i][j] == 'N'
				|| cub3d->map[i][j] == 'S' || cub3d->map[i][j] == 'E'
				|| cub3d->map[i][j] == 'W')
			{
				if (i == 0 || i == cub3d->map_length - 1
					|| !check_wall(cub3d->map[i][j + 1])
					|| !check_wall(cub3d->map[i][j - 1])
					|| !check_wall(cub3d->map[i + 1][j])
					|| !check_wall(cub3d->map[i - 1][j]) || cub3d->count != 1)
					p_error("Invalid map");
			}
			j++;
		}
		i++;
	}
}

void	is_txt_avail(t_cub3d *cub3d)
{
	if (open(cub3d->west_texture, O_RDONLY) == -1
		|| open(cub3d->north_texture, O_RDONLY) == -1
		|| open(cub3d->east_texture, O_RDONLY) == -1
		|| open(cub3d->south_texture, O_RDONLY) == -1)
		p_error("Invalid Resources");
}

void	read_map_elements(t_cub3d *cub3d)
{
	char	**read;

	cub3d->map = NULL;
	cub3d->count = 0;
	cub3d->east_texture = NULL;
	cub3d->west_texture = NULL;
	cub3d->south_texture = NULL;
	cub3d->north_texture = NULL;
	cub3d->f_c_flag = 0;
	cub3d->txt_flag = 0;
	cub3d->ceiling_color = -1;
	cub3d->floor_color = -1;
	read = read_file(cub3d);
	get_map_layout(cub3d, read);
	if (!cub3d->map)
		p_error("Invalid map");
	free_strs(read, 0);
	parse_map(cub3d);
	is_txt_avail(cub3d);
}
