/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ddaUtils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:41:21 by momihamm          #+#    #+#             */
/*   Updated: 2024/02/19 13:30:52 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	get_curnt_posi(t_play *parzival, t_cub3d *yous)
{
	int	row;
	int	clm;

	row = 0;
	while (yous->map[row])
	{
		clm = 0;
		while (yous->map[row][clm])
		{
			if (check_is_player(parzival, yous->map[row][clm]) == 1)
			{
				parzival->x_play = (double) clm * 32;
				parzival->y_play = (double) row * 32;
				return ;
			}
			clm++;
		}
		row++;
	}
	return ;
}
