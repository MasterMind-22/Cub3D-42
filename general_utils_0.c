/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:48:58 by momihamm          #+#    #+#             */
/*   Updated: 2024/02/22 22:08:10 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	the_longest_line(t_cub3d *usef, t_ray *my_struct)
{
	int	big_len;
	int	row;

	big_len = 0;
	row = 0;
	while (usef->map[row])
	{
		if ((int)ft_strlen (usef->map[row]) > big_len)
			big_len = (int)ft_strlen(usef->map[row]);
		row++;
	}
	my_struct->the_long_line = big_len;
	my_struct->the_rows = row;
}

double	deg2rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double	rad2deg(double radians)
{
	return (radians * (180.0 / M_PI));
}
// window 320 x 200;
// distance between rays = 60 / 320;