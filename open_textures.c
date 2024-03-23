/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 06:20:23 by yonadry           #+#    #+#             */
/*   Updated: 2024/03/23 08:34:49 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	get_data_addr(t_ray *strahl)
{
	strahl->north_texture->data_addr
		= mlx_get_data_addr(strahl->north_texture->mlx_img,
			&strahl->north_texture->intperpixl,
			&strahl->north_texture->lenofline,
			&strahl->north_texture->end);
	strahl->east_texture->data_addr
		= mlx_get_data_addr(strahl->east_texture->mlx_img,
			&strahl->east_texture->intperpixl, &strahl->east_texture->lenofline,
			&strahl->east_texture->end);
	strahl->south_texture->data_addr
		= mlx_get_data_addr(strahl->south_texture->mlx_img,
			&strahl->south_texture->intperpixl,
			&strahl->south_texture->lenofline,
			&strahl->south_texture->end);
	strahl->west_texture->data_addr
		= mlx_get_data_addr(strahl->west_texture->mlx_img,
			&strahl->west_texture->intperpixl,
			&strahl->west_texture->lenofline,
			&strahl->west_texture->end);
	if (!strahl->north_texture->data_addr || !strahl->east_texture->data_addr
		|| !strahl->south_texture->data_addr
		|| !strahl->west_texture->data_addr)
		return (free_all(strahl), p_error("Invalid Resources\n"));
}

void	open_textures(t_ray *strahl)
{
	strahl->north_texture->mlx_img = mlx_xpm_file_to_image(strahl->start,
			strahl->cub3d->north_texture,
			&strahl->north_texture->x, &strahl->north_texture->y);
	strahl->east_texture->mlx_img = mlx_xpm_file_to_image(strahl->start,
			strahl->cub3d->east_texture,
			&strahl->east_texture->x, &strahl->east_texture->y);
	strahl->south_texture->mlx_img = mlx_xpm_file_to_image(strahl->start,
			strahl->cub3d->south_texture,
			&strahl->south_texture->x, &strahl->south_texture->y);
	strahl->west_texture->mlx_img = mlx_xpm_file_to_image(strahl->start,
			strahl->cub3d->west_texture,
			&strahl->west_texture->x, &strahl->west_texture->y);
	if (!strahl->north_texture->mlx_img || !strahl->east_texture->mlx_img
		|| !strahl->south_texture->mlx_img || !strahl->west_texture->mlx_img)
		p_error("Invalid Resources\n");
	get_data_addr(strahl);
}
