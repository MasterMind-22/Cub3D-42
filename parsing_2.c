/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 05:56:50 by yonadry           #+#    #+#             */
/*   Updated: 2024/03/23 08:31:39 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	save_colors(t_cub3d *cub3d, char **colors, char c)
{
	int	i;
	int	j;

	i = -1;
	while (colors[++i])
	{
		j = -1;
		while (colors[i][++j])
		{
			if (colors[i][j] < '0' || colors[i][j] > '9')
				return (1);
		}
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
			return (1);
	}
	if (c == 'C')
		cub3d->ceiling_color = deci_to_hexa_color(
				ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	if (c == 'F')
		cub3d->floor_color = deci_to_hexa_color(
				ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	free_strs(colors, 0);
	return (0);
}

int	check_colors(t_cub3d *cub3d, char **split)
{
	int		i;
	int		start;
	int		c;
	char	**colors;

	i = 0;
	c = 0;
	colors = malloc(sizeof(char *) * 4);
	while (i < (int)ft_strlen(split[1]))
	{
		if (split[1][i] != GRID_SIZE)
		{
			start = i;
			while ((split[1][i] && split[1][i] != ',')
					|| (split[1][i] && !split[1][i + 1]))
				i++;
			colors[c++] = ft_substr(split[1], start, i - start);
		}
		i++;
	}
	colors[c] = NULL;
	if (c != 3 || save_colors(cub3d, colors, split[0][0]))
		return (free_strs(colors, 0), 1);
	return (0);
}

void	check_textures_norm(t_cub3d *cub3d, char **split)
{
	if (cub3d->f_c_flag == 1 && (!cub3d->east_texture || !cub3d->west_texture
			|| !cub3d->south_texture || !cub3d->north_texture)
		&& (!cub3d->floor_color || !cub3d->ceiling_color))
		p_error("Wrong Elements");
	if (!ft_strncmp(split[0], "NO", 2) || !ft_strncmp(split[0], "SO", 2)
		|| !ft_strncmp(split[0], "WE", 2) || !ft_strncmp(split[0], "EA", 2))
		cub3d->txt_flag++;
	if ((!ft_strncmp(split[0], "NO", 2) && cub3d->north_texture)
		|| (!ft_strncmp(split[0], "SO", 2) && cub3d->south_texture)
		|| (!ft_strncmp(split[0], "WE", 2) && cub3d->west_texture)
		|| (!ft_strncmp(split[0], "EA", 2) && cub3d->east_texture)
		|| (!ft_strncmp(split[0], "F", 1) && cub3d->floor_color >= 0)
		|| (!ft_strncmp(split[0], "C", 1) && cub3d->ceiling_color >= 0))
		p_error("Duplicated Resources");
}

void	check_textures(t_cub3d *cub3d, char **split)
{
	check_textures_norm(cub3d, split);
	if (!ft_strncmp(split[0], "NO", 2) && !cub3d->f_c_flag)
		cub3d->north_texture = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "EA", 2) && !cub3d->f_c_flag)
		cub3d->east_texture = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "SO", 2) && !cub3d->f_c_flag)
		cub3d->south_texture = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "WE", 2) && !cub3d->f_c_flag)
		cub3d->west_texture = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "F", 1) || !ft_strncmp(split[0], "C", 1))
	{
		cub3d->f_c_flag++;
		if (cub3d->f_c_flag == 2 && cub3d->txt_flag && cub3d->txt_flag < 4)
			p_error("Invalid Resources");
		else if (cub3d->f_c_flag == 2)
			cub3d->f_c_flag = 0;
		if (count_char(split[1], ',') > 2 || check_colors(cub3d, split))
			p_error("Invalid color");
	}
	else
		p_error("Invalid color");
}

char	*fill_empty_space_in_map(t_cub3d *cub3d, char *str, char **read)
{
	size_t	i;
	size_t	longest;
	char	*result;

	i = -1;
	longest = 0;
	while (++i < cub3d->map_length)
		if (ft_strlen(read[i]) > longest)
			longest = ft_strlen(read[i]) - 1;
	result = malloc(sizeof(char) * (longest + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			result[i] = '+';
		else
			result[i] = str[i];
	}
	while (i < longest)
		result[i++] = '+';
	result[i] = '\0';
	return (result);
}
