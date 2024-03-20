/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_a_binary_to_a_game.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:41:58 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/20 03:03:46 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	determine_ange(t_ray *jackboys, int id)
{
	jackboys->dataray[id].ray_ang = fmod (jackboys->dataray[id].ray_ang,
			2 * M_PI);
	if (jackboys->dataray[id].ray_ang < 0)
		jackboys->dataray[id].ray_ang = (2 * M_PI)
			+ jackboys->dataray[id].ray_ang;
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
		obj->dataray[id].horz = 0;
		dda (obj, obj->dataray[id].x_found_wall, obj->dataray[id].y_found_wall);
	}
	else
	{
		obj->dataray[id].x_found_wall = obj->dataray[id].horzwall_hit_x;
		obj->dataray[id].y_found_wall = obj->dataray[id].horzwall_hit_y;
		obj->dataray[id].massafa = obj->dataray[id].hor_massafa;
		obj->dataray[id].horz = 1;
		obj->dataray[id].virt = 0;
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

// int select_texture(t_ray *obj, int id)
// {
// 	puts("select_texture");
// 	printf("up = %d\n", is_ray_down(obj->dataray[id].ray_ang));
// 	printf("horz = %d\n", obj->dataray[id].horz);
// 	if (is_ray_down(obj->dataray[id].ray_ang) && obj->dataray[id].horz == 1)
// 	{
// 		puts("north");
// 		// obj->right_texture->data_addr = obj->north_texture->data_addr;
// 		// obj->right_texture->lenofline = obj->north_texture->lenofline;
// 		// obj->right_texture->intperpixl = obj->north_texture->intperpixl;
// 		return 1;
// 	}
// 	else if (is_ray_up(obj->dataray[id].ray_ang) && obj->dataray[id].horz == 1)
// 	{
// 		puts("south");
// 			// obj->right_texture->data_addr = obj->south_texture->data_addr;
// 			// obj->right_texture->lenofline = obj->south_texture->lenofline;
// 			// obj->right_texture->intperpixl = obj->south_texture->intperpixl;
// 		return 1;
	
// 	}
// 	else if (is_ray_left(obj->dataray[id].ray_ang) && obj->dataray[id].virt == 1)
// 	{
// 		puts("west");
// 		// obj->right_texture->data_addr = obj->west_texture->data_addr;
// 		// obj->right_texture->lenofline = obj->west_texture->lenofline;
// 		// obj->right_texture->intperpixl = obj->west_texture->intperpixl;
// 		return 1;
// 	}
// 	else if (is_ray_right(obj->dataray[id].ray_ang) && obj->dataray[id].virt == 1)
// 	{
// 		puts("east");
// 			// obj->right_texture->data_addr = obj->east_texture->data_addr;
// 			// obj->right_texture->lenofline = obj->east_texture->lenofline;
// 			// obj->right_texture->intperpixl = obj->east_texture->intperpixl;
// 		return 1;
	
// 	}
// 	return 0;
// }

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
// 	select_texture (obj, obj->id);
// 	mlx_put_image_to_window (obj->start, obj->window,
// 		obj->my_image->mlx_img, 0, 0);
// 	return (0);
// }
