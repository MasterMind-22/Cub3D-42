/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 04:47:29 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/16 04:47:48 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	left(t_ray *obj)
{
	double	old_x;
	double	old_y;

	old_x = obj->plays->x_play;
	old_y = obj->plays->y_play;
	if (obj->plays->left_walk == 1)
	{
		obj->plays->fake_angle = obj->plays->rot_ang - (M_PI / 2);
		obj->plays->x_play += cos(obj->plays->fake_angle);
		obj->plays->y_play += sin(obj->plays->fake_angle);
		if ((is_wall (obj, obj->plays->x_play, obj->plays->y_play) == -1))
		{
			obj->plays->x_play = old_x;
			obj->plays->y_play = old_y;
		}
	}
}

void	right(t_ray *obj)
{
	double	old_x;
	double	old_y;

	old_x = obj->plays->x_play;
	old_y = obj->plays->y_play;
	if (obj->plays->right_walk == 1)
	{
		obj->plays->fake_angle = obj->plays->rot_ang + (M_PI / 2);
		obj->plays->x_play += cos(obj->plays->fake_angle);
		obj->plays->y_play += sin(obj->plays->fake_angle);
		if ((is_wall (obj, obj->plays->x_play, obj->plays->y_play) == -1))
		{
			obj->plays->x_play = old_x;
			obj->plays->y_play = old_y;
		}
	}
}
