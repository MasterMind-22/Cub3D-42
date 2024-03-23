/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 06:01:33 by yonadry           #+#    #+#             */
/*   Updated: 2024/03/23 08:41:48 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	get_map(t_cub3d *cub3d, char **read)
{
	int		i;
	char	*tmp;

	i = 0;
	while (read[i])
		i++;
	cub3d->map_length = i;
	cub3d->map = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (read[i])
	{
		tmp = ft_strtrim(read[i], "\n");
		if (is_that_char(tmp))
			p_error("Invalid map");
		cub3d->map[i] = fill_empty_space_in_map(cub3d, tmp, read);
		free(tmp);
		if (!ft_strlen(cub3d->map[i])
			|| (count_char(read[i], '\n') && !read[i + 1]))
			p_error("Invalid map");
		i++;
	}
	cub3d->map[i] = NULL;
}

void	get_map_layout(t_cub3d *cub3d, char **read)
{
	char	*str;
	char	**split;
	int		i;

	i = 0;
	while (read[i])
	{
		if (!read[i])
			p_error("Invalid file");
		str = ft_strtrim(read[i], "\n ");
		split = ft_split(str, ' ');
		free(str);
		if (split[0] && split[1] && !split[2])
			check_textures(cub3d, split);
		if ((count_char(read[i], '1') || count_char(read[i], '0'))
			&& (count_char(split[0], '1') || count_char(split[0], '0')))
		{
			free_strs(split, 0);
			get_map(cub3d, &read[i]);
			return ;
		}
		free_strs(split, 0);
		i++;
	}
}

char	**read_file(t_cub3d *cub3d)
{
	char	**file_content;
	char	*str;
	int		i;
	int		fd;

	i = 0;
	fd = open(cub3d->file_name, O_RDONLY);
	file_content = malloc(file_col_num(cub3d) * sizeof(char *));
	str = get_next_line(fd);
	if (!str)
		p_error("Empty file");
	while (str)
	{
		file_content[i] = ft_strdup(str);
		i++;
		free(str);
		str = get_next_line(fd);
	}
	file_content[i] = NULL;
	close(fd);
	return (file_content);
}

void	more_checks(t_cub3d *cub3d)
{
	size_t	i;

	i = -1;
	while (++i < cub3d->map_length)
	{
		cub3d->count += count_char(cub3d->map[i], 'E');
		cub3d->count += count_char(cub3d->map[i], 'W');
		cub3d->count += count_char(cub3d->map[i], 'N');
		cub3d->count += count_char(cub3d->map[i], 'S');
	}
	if (cub3d->ceiling_color == -1 || cub3d->floor_color == -1)
		p_error("Invalid color");
}

int	check_wall(char c)
{
	if (c == '1' || c == 'N' || c == '0' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}
