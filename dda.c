/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:01:43 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/02 02:12:59 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

// void	new_posi(t_ray *parzi)
// {
// 	int	row;
// 	int	clm;

// 	row = 0;
// 	while (parzi->game_map[row])
// 	{
// 		clm = 0;
// 		while (parzi->game_map[row][clm])
// 		{
// 			if (check_is_player(parzi->game_map[row][clm]) == 1)
// 			{
// 				parzi->plays->x_play = clm;
// 				parzi->plays->y_play = row;
// 				return ;
// 			}
// 			clm++;
// 		}
// 		row++;
// 	}
// }

void	dda(t_ray *obj, double x1, double y1)
{
	int	indx;

	indx = 0;
	obj->algo->x_zero = (obj->plays->x_play) + 16;
	obj->algo->y_zero = (obj->plays->y_play) + 16;
	obj->algo->dx = x1 - obj->algo->x_zero;
	obj->algo->dy = y1 - obj->algo->y_zero;
	if (fabs (obj->algo->dx) > fabs(obj->algo->dy))
		obj->algo->steps = fabs(obj->algo->dx);
	else
		obj->algo->steps = fabs(obj->algo->dy);
	obj->algo->x_incre = obj->algo->dx / (double) obj->algo->steps;
	obj->algo->y_incre = obj->algo->dy / (double) obj->algo->steps;
	obj->algo->flo_x = obj->algo->x_zero;
	obj->algo->flo_y = obj->algo->y_zero;
	while (indx <= obj->algo->steps)
	{
		put_pix_img(obj->my_image, obj->algo->flo_x,
			obj->algo->flo_y, obj->colur);
		obj->algo->flo_x += obj->algo->x_incre;
		obj->algo->flo_y += obj->algo->y_incre;
		indx++;
	}
}
