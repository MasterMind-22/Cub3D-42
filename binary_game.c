/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:39:39 by momihamm          #+#    #+#             */
/*   Updated: 2024/02/23 16:16:02 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_line(t_ray *obj)
{
	int	x;
	int	y;
	int	var;
	int	val;

	x = 0;
	val = 0;
	while (x < 9)
	{
		y = 0;
		var = 0;
		while (y < 9)
		{
			put_pix_img (obj->my_image, (obj->plays->x_play + 12) + var,
				(obj->plays->y_play + 12) + val, obj->colur);
			y++;
			var++;
		}
		x++;
		val++;
	}
	obj->colur = 0x00FF1A;
	dda(obj,
		((obj->plays->x_play) + 16) + cos(obj->plays->rot_ang) * 80,
		((obj->plays->y_play) + 16) + sin(obj->plays->rot_ang) * 80);
}

void	creat_img(t_ray *obj)
{
	mlx_clear_window (obj->start, obj->window);
	mlx_destroy_image (obj->start, obj->my_image->mlx_img);
	make_valus(obj->plays, obj);
	obj->my_image->mlx_img = mlx_new_image (obj->start, obj->the_long_line * 32,
			obj->the_rows * 32);
	obj->my_image->data_addr = mlx_get_data_addr (obj->my_image->mlx_img,
			&obj->my_image->intperpixl, &obj->my_image->lenofline,
			&obj->my_image->end);
}
