/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_my_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:58:36 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/16 08:26:49 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	init_player(t_ray *ready, t_cub3d *usef)
{
	get_curnt_posi (ready->plays, usef);
	ready->plays->turn_d = 0;
	ready->plays->walk_d = 0;
	ready->plays->move_speed = 60.0;
	ready->plays->rotation_speed = 2 * (M_PI / 180);
	ready->plays->f_o_v = deg2rad (60.00);
	ready->plays->pixel_per_colum = 1;
	ready->plays->num_of_rays = RAYS_WINDOW_WIDTH;
	ready->my_image->win_w = ready->the_long_line * GRID_SIZE;
	ready->my_image->win_h = ready->the_rows * GRID_SIZE;
	ready->dest_por_wall = (RAYS_WINDOW_WIDTH / 2)
		/ tan (ready->plays->f_o_v / 2);
	ready->ceiling = usef->ceiling_color;
	ready->f_flor = usef->floor_color;
}

void	init_cast(t_ray *starlight)
{
	starlight->plays->tile = GRID_SIZE;
	starlight->plays->x_move = 0;
	starlight->plays->y_move = 0;
}

void	init_ptr(t_ray *parzi, int id)
{
	parzi->dataray[id].next_h_x = 0;
	parzi->dataray[id].next_h_y = 0;
	parzi->dataray[id].first_hit_x = 0;
	parzi->dataray[id].first_hit_y = 0;
	parzi->dataray[id].vir_wall_hit_x = 0;
	parzi->dataray[id].vir_wall_hit_y = 0;
	parzi->dataray[id].horzwall_hit_x = 0;
	parzi->dataray[id].horzwall_hit_y = 0;
	parzi->dataray[id].hor_massafa = 0;
	parzi->dataray[id].vir_massafa = 0;
	parzi->dataray[id].next_vir_x = 0;
	parzi->dataray[id].next_vir_y = 0;
	parzi->dataray[id].massafa = 0;
	parzi->dataray[id].virt = 0;
	parzi->dataray[id].horz = 0;
}

int	check_is_player(t_play *obj, char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (c == 'N')
			obj->rot_ang = 3 * M_PI / 2;
		if (c == 'S')
			obj->rot_ang = M_PI / 2;
		if (c == 'E')
			obj->rot_ang = 0;
		if (c == 'W')
			obj->rot_ang = M_PI;
		return (1);
	}
	return (0);
}
