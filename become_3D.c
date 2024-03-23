/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   become_3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 05:00:34 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/23 08:13:30 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	get_pixel_color(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->data_addr + (y * data->lenofline + x * (data->intperpixl / 8));
	return (*(unsigned int *)dst);
}

void	ceiling_floor(t_ray *obj)
{
	int	indx;
	int	rows;

	indx = 0;
	while (indx < RAYS_WINDOW_WIDTH)
	{
		rows = 0;
		while (rows < WINDOW_HEIGHT)
		{
			if (rows <= (WINDOW_HEIGHT / 2))
				obj->colur = obj->ceiling;
			else
				obj->colur = obj->f_flor;
			put_pix_img (obj->my_image, indx, rows, obj->colur);
			rows++;
		}
		indx++;
	}
}

int	select_texture_norm(t_ray *obj, int id)
{
	if (obj->dataray[id].is_up == 0 && obj->dataray[id].horz == 1)
	{
		obj->right_texture->data_addr = obj->north_texture->data_addr;
		obj->right_texture->lenofline = obj->north_texture->lenofline;
		obj->right_texture->intperpixl = obj->north_texture->intperpixl;
		obj->right_texture->x = obj->north_texture->x;
		obj->right_texture->y = obj->north_texture->y;
		return (1);
	}
	else if (!obj->dataray[id].is_down && obj->dataray[id].horz == 1)
	{
		obj->right_texture->data_addr = obj->south_texture->data_addr;
		obj->right_texture->lenofline = obj->south_texture->lenofline;
		obj->right_texture->intperpixl = obj->south_texture->intperpixl;
		obj->right_texture->x = obj->south_texture->x;
		obj->right_texture->y = obj->south_texture->y;
		return (1);
	}
	return (0);
}

int	select_texture(t_ray *obj, int id)
{
	obj->dataray[id].is_up = is_ray_up(obj->dataray[id].ray_ang);
	obj->dataray[id].is_down = is_ray_down(obj->dataray[id].ray_ang);
	obj->dataray[id].is_left = is_ray_left(obj->dataray[id].ray_ang);
	obj->dataray[id].is_right = is_ray_right(obj->dataray[id].ray_ang);
	if (select_texture_norm(obj, id))
		return (1);
	else if (!obj->dataray[id].is_right && obj->dataray[id].virt == 1)
	{
		obj->right_texture->data_addr = obj->west_texture->data_addr;
		obj->right_texture->lenofline = obj->west_texture->lenofline;
		obj->right_texture->intperpixl = obj->west_texture->intperpixl;
		obj->right_texture->x = obj->west_texture->x;
		obj->right_texture->y = obj->west_texture->y;
		return (1);
	}
	else if (obj->dataray[id].is_left == 0 && obj->dataray[id].virt == 1)
	{
		obj->right_texture->data_addr = obj->east_texture->data_addr;
		obj->right_texture->lenofline = obj->east_texture->lenofline;
		obj->right_texture->intperpixl = obj->east_texture->intperpixl;
		obj->right_texture->x = obj->east_texture->x;
		obj->right_texture->y = obj->east_texture->y;
		return (1);
	}
	return (0);
}

void	draw_wall(t_ray *obj, int id, int walltoppixel, int wallbottompixel)
{
	int		y;
	int		texturexffsetx;
	double	distancefromtop;
	int		textureoffsety;
	int		color;

	if (obj->dataray[id].virt)
		texturexffsetx = fmod((obj->dataray[id].y_found_wall), GRID_SIZE);
	else
		texturexffsetx = fmod((obj->dataray[id].x_found_wall), GRID_SIZE);
	texturexffsetx *= (obj->right_texture->x / (double)GRID_SIZE);
	y = walltoppixel;
	while (y < wallbottompixel)
	{
		distancefromtop = y + (obj->dataray[id].wall_length / 2)
			- (WINDOW_HEIGHT / 2);
		textureoffsety = distancefromtop * ((double)GRID_SIZE
				/ obj->dataray[id].wall_length);
		textureoffsety *= (obj->right_texture->y
				/ (double)GRID_SIZE);
		color = get_pixel_color(obj->right_texture,
				texturexffsetx, textureoffsety);
		put_pix_img (obj->my_image, id, y, color);
		y++;
	}
}
