/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 01:50:22 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/14 02:10:49 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	is_ray_down(double ray_angle)
{
	return (ray_angle > 0 && ray_angle < M_PI);
}

int	is_ray_up(double ray_angle)
{
	return (!is_ray_down(ray_angle));
}

int	is_ray_right(double ray_angle)
{
	if (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2)
		return (1);
	return (0);
}

int	is_ray_left(double ray_angle)
{
	return (!is_ray_right(ray_angle));
}
