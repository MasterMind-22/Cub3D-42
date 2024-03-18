/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_a_binary_to_a_game.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:41:58 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/16 08:27:51 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	determine_ange(t_ray *jackboys, int id)
{
	jackboys->dataray[id].ray_ang = fmod (jackboys->dataray[id].ray_ang,
			2 * M_PI);
	if (jackboys->dataray[id].ray_ang < 0)
		jackboys->dataray[id].ray_ang = (2 * M_PI)
			+ jackboys->dataray[id].ray_ang ;
}

void	chose_vert_or_horz(t_ray *obj, int id)
{
	calcul_hor_and_ver_dessetens (obj, id);
	obj->colur = 0xFFFFFF;
	if (obj->dataray[id].hor_massafa > obj->dataray[id].vir_massafa)
	{
		obj->dataray[id].x_found_wall = obj->dataray[id].vir_wall_hit_x;
		obj->dataray[id].y_found_wall = obj->dataray[id].vir_wall_hit_y;
		obj->dataray[id].massafa = obj->dataray[id].vir_massafa;
		obj->dataray[id].virt = 1;
		dda (obj, obj->dataray[id].x_found_wall, obj->dataray[id].y_found_wall);
	}
	else
	{
		obj->dataray[id].x_found_wall = obj->dataray[id].horzwall_hit_x;
		obj->dataray[id].y_found_wall = obj->dataray[id].horzwall_hit_y;
		obj->dataray[id].massafa = obj->dataray[id].hor_massafa;
		obj->dataray[id].horz = 1;
		dda (obj, obj->dataray[id].x_found_wall, obj->dataray[id].y_found_wall);
	}
}

void	cast_an_ray(t_ray *bayren, int id)
{
	init_ptr (bayren, id);
	chose_vert_or_horz (bayren, id);
}

void	casting(t_ray *parzi)
{
	parzi->id = 0;
	init_cast (parzi);
	parzi->dataray[parzi->id].ray_ang = parzi->plays->rot_ang;
	parzi->dataray[parzi->id].ray_ang -= parzi->plays->f_o_v / 2;
	while (parzi->id < RAYS_WINDOW_WIDTH)
	{
		cast_an_ray (parzi, parzi->id);
		parzi->dataray[parzi->id + 1].ray_ang
			= parzi->dataray[parzi->id].ray_ang ;
		parzi->id++;
		parzi->dataray[parzi->id].ray_ang += parzi->plays->f_o_v
			/ RAYS_WINDOW_WIDTH;
	}
}

int	ft_again(t_ray *obj)
{
	creat_img (obj);
	casting(obj);
	ceiling_floor (obj);
	become_3d (obj);
	mlx_put_image_to_window (obj->start, obj->window,
		obj->my_image->mlx_img, 0, 0);
	return (0);
}

// int	ft_again(t_ray *obj)
// {
// 	int		row;
// 	int		clm;

// 	row = 0;
// 	creat_img (obj);
// 	while (obj->game_map[row])
// 	{
// 		clm = 0;
// 		while (obj->game_map[row][clm])
// 		{
// 			if (obj->game_map[row][clm] == '1')
// 				make_square(row, clm, obj);
// 			else if (obj->game_map[row][clm] == '+')
// 				make_square (row, clm, obj);
// 			clm++;
// 		}
// 		row++;
// 	}
// 	obj->colur = 0x00FF1A;
// 	casting(obj);
// 	draw_line (obj);
// 	mlx_put_image_to_window (obj->start, obj->window,
// 		obj->my_image->mlx_img, 0, 0);
// 	return (0);
// }
