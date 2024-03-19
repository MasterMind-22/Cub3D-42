/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:44:11 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/15 00:43:27 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	player_and_culor(t_ray *obj, int row, int clm)
{
	if (obj->game_map[row][clm] == '1')
		obj->colur = 0x005EFF;
	else if ((obj->game_map[row][clm]) == '+')
		obj->colur = 0x000000;
	else
		obj->colur = 0xFF0000;
}

void	make_square(int row, int clm, t_ray *object)
{
	int	var[5];

	var[0] = 0;
	var[1] = clm * GRID_SIZE;
	var[2] = row * GRID_SIZE;
	var[3] = GRID_SIZE;
	player_and_culor (object, row, clm);
	while (var[0] < var[3])
	{
		var[4] = 0;
		while (var[4] < var[3])
		{
			put_pix_img (object->my_image, var[0] + var[1], var[4] + var[2],
				object->colur);
			var[4]++;
		}
		var[0]++;
	}
}
