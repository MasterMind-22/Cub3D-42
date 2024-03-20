/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   become_3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 05:00:34 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/20 03:05:08 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"



int    get_pixel_color(t_img *data, int x, int y)
{
    char    *dst;

    dst = data->data_addr + (y * data->lenofline + x * (data->intperpixl / 8));
    return (*(unsigned int *)dst);
}

// void	make_rege(t_ray *obj, double tol, double ard, int id)
// {
// 	double	x;
// 	double	y;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	x = id * 1;
// 	y = (WINDOW_HEIGHT / 2) - (obj->dataray[id].wall_length / 2);
// 	obj->colur = 0x000099;


// 	int textureOffsetX;
// 	if (obj->dataray[id].virt)
// 		textureOffsetX = (int)obj->dataray[id].y_found_wall % GRID_SIZE;
// 	else
// 		textureOffsetX = (int)obj->dataray[id].x_found_wall % GRID_SIZE;
// 	while (i < ard)
// 	{
// 		j = 0;
// 		while (j < tol)
// 		{
// 			int distanceFromTop = y + (obj->dataray[id].wall_length / 2) - (WINDOW_HEIGHT / 2);
// 			int textureOffsetY = distanceFromTop * ((float)GRID_SIZE / obj->dataray[id].wall_length);
// 			unsigned int color  = get_color(obj, textureOffsetX, textureOffsetY);
// 			// printf ("%d\n", textureOffsetY);
// 			put_pix_img (obj->my_image, i + x, y + j,
// 				color);
// 			j++;
// 			y++;
// 		}
// 		i++;
// 	}
// }

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

int select_texture(t_ray *obj, int id)
{
	// printf("%d obj->dataray[id].is_up\n", is_ray_down (obj->dataray[id].ray_ang));
	// printf("%d obj->dataray[id].is_down\n", obj->dataray[id].is_down);
	// printf("%d obj->dataray[id].is_left\n", obj->dataray[id].is_left);
	// printf("%d obj->dataray[id].is_right\n", obj->dataray[id].is_right);
	// printf("%d obj->dataray[id].horz\n", obj->dataray[id].horz);
	// printf("%d obj->dataray[id].virt\n", obj->dataray[id].virt);
	obj->dataray[id].is_up = is_ray_up(obj->dataray[id].ray_ang);
	obj->dataray[id].is_down = is_ray_down(obj->dataray[id].ray_ang);
	obj->dataray[id].is_left = is_ray_left(obj->dataray[id].ray_ang);
	obj->dataray[id].is_right = is_ray_right(obj->dataray[id].ray_ang);
	printf ("kmi\n");
	if (obj->dataray[id].is_up == 0 && obj->dataray[id].horz == 1)
	{
		puts("north");
		obj->right_texture->data_addr = obj->north_texture->data_addr;
		obj->right_texture->lenofline = obj->north_texture->lenofline;
		obj->right_texture->intperpixl = obj->north_texture->intperpixl;
		obj->right_texture->x = obj->north_texture->x;
		return 1;
	}
	else if (!obj->dataray[id].is_down && obj->dataray[id].horz == 1)
	{
		puts("south");
			obj->right_texture->data_addr = obj->south_texture->data_addr;
			obj->right_texture->lenofline = obj->south_texture->lenofline;
			obj->right_texture->intperpixl = obj->south_texture->intperpixl;
			obj->right_texture->x = obj->south_texture->x;
		return 1;
	
	}
	else if (!obj->dataray[id].is_right && obj->dataray[id].virt == 1)
	{
		puts("west");
		obj->right_texture->data_addr = obj->west_texture->data_addr;
		obj->right_texture->lenofline = obj->west_texture->lenofline;
		obj->right_texture->intperpixl = obj->west_texture->intperpixl;
		obj->right_texture->x = obj->west_texture->x;
		return 1;
	}
	else if (obj->dataray[id].is_left == 0 && obj->dataray[id].virt == 1)
	{
		puts("east");
			obj->right_texture->data_addr = obj->east_texture->data_addr;
			obj->right_texture->lenofline = obj->east_texture->lenofline;
			obj->right_texture->intperpixl = obj->east_texture->intperpixl;
			obj->right_texture->x = obj->east_texture->x;
		return 1;
	
	}
	return 0;
}

void	become_3d(t_ray *obj)
{
	int		id;
	double	corect_lenght;
unsigned int color;
	id = 0;
	while (id < RAYS_WINDOW_WIDTH)
	{
		corect_lenght = obj->dataray[id].massafa
			* cos (obj->dataray[id].ray_ang - obj->plays->rot_ang);
		obj->dataray[id].wall_length = (obj->plays->tile / corect_lenght) * obj->dest_por_wall;
		
        int wallTopPixel = (WINDOW_HEIGHT / 2) - (obj->dataray[id].wall_length / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (WINDOW_HEIGHT / 2) + (obj->dataray[id].wall_length / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

		int y = (WINDOW_HEIGHT / 2) - (obj->dataray[id].wall_length / 2);
		// obj->colur = 0x000099;


	select_texture(obj, id);
	int textureOffsetX;
	if (obj->dataray[id].virt)
		textureOffsetX = ((int)obj->dataray[id].y_found_wall) % obj->right_texture->x;
	else
		textureOffsetX = ((int)obj->dataray[id].x_found_wall) % obj->right_texture->x;
	for (int y  = wallTopPixel; y < wallBottomPixel; y++)
	{

			int distanceFromTop = y + (obj->dataray[id].wall_length / 2) - (WINDOW_HEIGHT / 2);
			int textureOffsetY = distanceFromTop * ((double)obj->right_texture->x / obj->dataray[id].wall_length);
				color  = get_pixel_color(obj->right_texture, textureOffsetX, textureOffsetY);
			put_pix_img (obj->my_image, id, y, color);
	}
		id++;
	}
}
