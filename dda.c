/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:01:43 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/14 02:10:31 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	dda(t_ray *obj, double x1, double y1)
{
	int	indx;

	indx = 0;
	obj->algo->x_zero = (obj->plays->x_play);
	obj->algo->y_zero = (obj->plays->y_play);
	obj->algo->dx = x1 - obj->algo->x_zero;
	obj->algo->dy = y1 - obj->algo->y_zero;
	if (fabs (obj->algo->dx) > fabs(obj->algo->dy))
		obj->algo->steps = fabs(obj->algo->dx);
	else
		obj->algo->steps = fabs(obj->algo->dy);
	obj->algo->x_incre = obj->algo->dx / obj->algo->steps;
	obj->algo->y_incre = obj->algo->dy / obj->algo->steps;
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
