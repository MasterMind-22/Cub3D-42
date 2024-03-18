/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   become_3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 05:00:34 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/16 08:22:41 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void get_data_addresses(t_ray *obj, int x, int y)
{
	obj->cub3d->east_texture = mlx_xpm_file_to_image(obj->my_image->mlx_img, obj->cub3d->east_texture, &x, &y);
	obj->cub3d->west_texture = mlx_xpm_file_to_image(obj->my_image->mlx_img, obj->cub3d->west_texture, &x, &y);
	obj->cub3d->north_texture = mlx_xpm_file_to_image(obj->my_image->mlx_img, obj->cub3d->north_texture, &x, &y);
	obj->cub3d->south_texture = mlx_xpm_file_to_image(obj->my_image->mlx_img, obj->cub3d->south_texture, &x, &y);
		if (!obj->cub3d->east_texture || !obj->cub3d->west_texture 
			|| !obj->cub3d->north_texture || !obj->cub3d->south_texture)
			return (exit(1));
}

void	make_rege(t_ray *obj, double tol, double ard, int id)
{
	double	x;
	double	y;
	int		i;
	int		j;

	i = 0;
	x = id * 1;
	y = 430 - (obj->dataray[id].wall_length / 2);
	obj->colur = 0x000099;

	get_data_addresses(obj, )
	uint32_t *colorBuffer = malloc(sizeof(uint32_t) * (uint32_t)WINDOW_HEIGHT * (uint32_t)RAYS_WINDOW_WIDTH);
	int wallStripHeight = (int)obj->dest_por_wall;
	int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
	if (wallTopPixel < 0)
		wallTopPixel = 0;

	int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
	if (wallBottomPixel > WINDOW_HEIGHT)
		wallBottomPixel = WINDOW_HEIGHT;
	
	uint32_t *walltext = malloc(sizeof(uint32_t) * 32 * 32);
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if ((j % 8) && (i % 8))
			{
				// puts("hello");
				walltext[(32 * i) + j] = 0xFF47F338;
			}
			else
				walltext[(32 * i) + j] = 0xD466566;
			// printf("%u\n", walltext[(32 * i) + j]);
		}
	}

	// // set color 
	// for (int i = 0; i < wallTopPixel; i++)
	// 	colorBuffer[(RAYS_WINDOW_WIDTH * i) + id] = 0xFF334433;
	
	int textureOffsetX;

	// printf ("y == %f || x == %f\n\n", obj->dataray[id].y_found_wall, obj->dataray[id].x_found_wall);
	if (obj->dataray[id].virt)
		textureOffsetX = ((int)obj->dataray[id].y_found_wall % 32);
	else
		textureOffsetX = ((int)obj->dataray[id].x_found_wall % 32);
	
	// for (int y = wallTopPixel; y< wallBottomPixel; y++)
	// {
	// }
	int distanceFromtop = y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
	int textureOffsetY = distanceFromtop * ((double)32 / wallStripHeight);
	uint32_t txtcolor = walltext[(32 * textureOffsetY) + textureOffsetX];
	for (int i = wallBottomPixel; i < WINDOW_HEIGHT; i++)
		colorBuffer[(WINDOW_HEIGHT * i) + id] = txtcolor;
	while (i < ard)
	{
		j = 0;
		while (j < tol)
		{

			// colorBuffer[(WINDOW_HEIGHT * i) + id] = txtcolor;
			put_pix_img (obj->my_image, i + x , y + j, txtcolor);
			j++;
		}
		
		i++;
	}
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

void	become_3d(t_ray *obj)
{
	int		id;
	double	corect_lenght;

	id = 0;
	while (id < RAYS_WINDOW_WIDTH)
	{
		corect_lenght = obj->dataray[id].massafa
			* cos (obj->dataray[id].ray_ang - obj->plays->rot_ang);
		obj->dataray[id].wall_length = (obj->plays->tile / corect_lenght)
			* obj->dest_por_wall;
		if (obj->dataray[id].wall_length > RAYS_WINDOW_WIDTH)
			obj->dataray[id].wall_length = RAYS_WINDOW_WIDTH;
		make_rege(obj, obj->dataray[id].wall_length, 0.5, id);
		id++;
	}
}
