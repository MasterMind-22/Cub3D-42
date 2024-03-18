/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:39:39 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/16 08:22:41 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_line(t_ray *obj)
{
	int	x;
	int	y;
	int	var;
	int	val;

	x = -1;
	val = 0;
	obj->colur = 0x00FF1A;
	while (++x < 9)
	{
		y = 0;
		var = 0;
		while (y < 9)
		{
			put_pix_img (obj->my_image, (obj->plays->x_play - 4) + var,
				(obj->plays->y_play - 4) + val, obj->colur);
			y++;
			var++;
		}
		val++;
	}
	obj->colur = 0x66B2FF;
	dda(obj,
		((obj->plays->x_play)) + cos(obj->plays->rot_ang) * 80,
		((obj->plays->y_play)) + sin(obj->plays->rot_ang) * 80);
}

void	creat_img(t_ray *obj)
{
	mlx_clear_window (obj->start, obj->window);
	mlx_destroy_image (obj->start, obj->my_image->mlx_img);
	make_valus(obj->plays, obj);
	obj->my_image->mlx_img = mlx_new_image (obj->start, RAYS_WINDOW_WIDTH,
			WINDOW_HEIGHT);
	obj->my_image->data_addr = mlx_get_data_addr (obj->my_image->mlx_img,
			&obj->my_image->intperpixl, &obj->my_image->lenofline,
			&obj->my_image->end);
}

void	draw_zero(t_ray *obj, t_play *parzi)
{
	int	row;
	int	clm;

	(void) parzi;
	row = 0;
	while (obj->game_map[row])
	{
		clm = 0;
		while (obj->game_map[row][clm])
		{
			if (check_is_player (obj->plays, obj->game_map[row][clm]) == 1)
				make_square (row, clm, obj);
			clm++;
		}
		row++;
	}
	draw_line (obj);
}

void	ft_draw(t_ray *object, t_play *parzi)
{
	int		row;
	int		clm;

	row = 0;
	while (object->game_map[row])
	{
		clm = 0;
		while (object->game_map[row][clm])
		{
			if (object->game_map[row][clm] == '1')
				make_square(row, clm, object);
			else if (object->game_map[row][clm] == '+')
				make_square (row, clm, object);
			clm++;
		}
		row++;
	}
	draw_zero (object, parzi);
	mlx_put_image_to_window (object->start, object->window,
		object->my_image->mlx_img, 0, 0);
}
