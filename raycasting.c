/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:36:21 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/20 03:03:46 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	the_first_hor_hit(t_ray *obj, int id)
{
	obj->dataray[id].first_hit_y = floor (obj->plays->y_play
			/ obj->plays->tile);
	obj->dataray[id].first_hit_y *= obj->plays->tile;
	if (is_ray_up(obj->dataray[id].ray_ang))
		obj->dataray[id].first_hit_y += obj->plays->tile;
	obj->dataray[id].first_hit_x = obj->plays->x_play
		+ (obj->dataray[id].first_hit_y - obj->plays->y_play)
		/ tan(obj->dataray[id].ray_ang);
	obj->plays->y_move = obj->plays->tile;
	if (is_ray_down(obj->dataray[id].ray_ang))
		obj->plays->y_move *= -1;
	obj->plays->x_move = obj->plays->tile
		/ tan(obj->dataray[id].ray_ang);
	if (is_ray_left(obj->dataray[id].ray_ang) && obj->plays->x_move > 0)
		obj->plays->x_move *= -1;
	if (is_ray_right(obj->dataray[id].ray_ang) && obj->plays->x_move < 0)
		obj->plays->x_move *= -1;
	obj->dataray[id].next_h_x = obj->dataray[id].first_hit_x;
	obj->dataray[id].next_h_y = obj->dataray[id].first_hit_y;
}

int	hor_hit(t_ray *bayren, int id)
{
	double	ch_y;

	determine_ange (bayren, id);
	the_first_hor_hit (bayren, id);
	while (bayren->dataray[id].next_h_x > 0
		&& bayren->dataray[id].next_h_x <= (bayren->the_long_line * GRID_SIZE)
		&& bayren->dataray[id].next_h_y > 0
		&& bayren->dataray[id].next_h_y <= (bayren->the_rows * GRID_SIZE))
	{
		ch_y = bayren->dataray[id].next_h_y;
		if (is_ray_down(bayren->dataray[id].ray_ang))
			ch_y = bayren->dataray[id].next_h_y - 1;
		if (is_ray_hit_wall (bayren, bayren->dataray[id].next_h_x, ch_y) == -1)
		{
			bayren->dataray[id].horzwall_hit_x = bayren->dataray[id].next_h_x;
			bayren->dataray[id].horzwall_hit_y = bayren->dataray[id].next_h_y;
			return (1);
		}
		else
		{
			bayren->dataray[id].next_h_x += bayren->plays->x_move;
			bayren->dataray[id].next_h_y += bayren->plays->y_move;
		}
	}
	return (0);
}

void	the_first_vir_hit(t_ray *obj, int id)
{
	obj->dataray[id].first_hit_x = floor (obj->plays->x_play
			/ obj->plays->tile) * obj->plays->tile;
	if (is_ray_right(obj->dataray[id].ray_ang))
		obj->dataray[id].first_hit_x += obj->plays->tile;
	obj->dataray[id].first_hit_y = obj->plays->y_play
		+ (obj->dataray[id].first_hit_x - obj->plays->x_play)
		* tan(obj->dataray[id].ray_ang);
	obj->plays->x_move = obj->plays->tile;
	if (is_ray_left(obj->dataray[id].ray_ang))
		obj->plays->x_move *= -1;
	obj->plays->y_move = obj->plays->tile * tan(obj->dataray[id].ray_ang);
	if (is_ray_down(obj->dataray[id].ray_ang) && obj->plays->y_move > 0)
		obj->plays->y_move *= -1;
	if (is_ray_up(obj->dataray[id].ray_ang) && obj->plays->y_move < 0)
		obj->plays->y_move *= -1;
	obj->dataray[id].next_vir_x = obj->dataray[id].first_hit_x;
	obj->dataray[id].next_vir_y = obj->dataray[id].first_hit_y;
}

int	vir_hit(t_ray *bayren, int id)
{
	double	x;

	determine_ange (bayren, id);
	the_first_vir_hit (bayren, id);
	while (bayren->dataray[id].next_vir_x > 0
		&& bayren->dataray[id].next_vir_x <= (bayren->the_long_line * GRID_SIZE)
		&& bayren->dataray[id].next_vir_y > 0
		&& bayren->dataray[id].next_vir_y <= (bayren->the_rows * GRID_SIZE))
	{
		x = bayren->dataray[id].next_vir_x;
		if (is_ray_left(bayren->dataray[id].ray_ang))
			x = bayren->dataray[id].next_vir_x - 1;
		if (is_ray_hit_wall (bayren, x, bayren->dataray[id].next_vir_y) == -1)
		{
			bayren->dataray[id].vir_wall_hit_x = bayren->dataray[id].next_vir_x;
			bayren->dataray[id].vir_wall_hit_y = bayren->dataray[id].next_vir_y;
			return (1);
		}
		else
		{
			bayren->dataray[id].next_vir_x += bayren->plays->x_move;
			bayren->dataray[id].next_vir_y += bayren->plays->y_move;
		}
	}
	return (0);
}

void	calcul_hor_and_ver_dessetens(t_ray *obj, int id)
{
	int	hit_ho;
	int	hit_vi;

	hit_ho = hor_hit(obj, id);
	hit_vi = vir_hit(obj, id);
	obj->dataray[id].hor_massafa = (double)sqrt(pow((
					obj->dataray[id].horzwall_hit_x
					- obj->plays->x_play), 2) + pow((
					obj->dataray[id].horzwall_hit_y
					- obj->plays->y_play), 2));
	obj->dataray[id].vir_massafa = (double)sqrt(pow((
					obj->dataray[id].vir_wall_hit_x
					- obj->plays->x_play), 2) + pow((
					obj->dataray[id].vir_wall_hit_y
					- obj->plays->y_play), 2));
	if (hit_ho == 0)
		obj->dataray[id].hor_massafa = 2147483647;
	if (hit_vi == 0)
		obj->dataray[id].vir_massafa = 2147483647;
}
