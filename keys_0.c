/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:28:57 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/16 04:47:54 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

char	*ft_strchr(const char *s, int c)
{
	int	indx;

	indx = 0;
	while (s[indx] != '\0')
	{
		if (s[indx] == (char)c)
			return ((char *) &s[indx]);
		indx++;
	}
	if ((char)c == '\0' && s[indx] == '\0')
		return ((char *)s + indx);
	return (NULL);
}

int	close_the_win(void)
{
	exit (0);
}

int	is_ray_hit_wall(t_ray *obj, double x, double y)
{
	int	row;
	int	clm;

	clm = floor (x / 32);
	row = floor (y / 32);
	if (row < obj->the_rows && clm < obj->the_long_line)
	{
		if (!ft_strchr("0NEWS", obj->game_map[row][clm]))
			return (-1);
	}
	return (0);
}

int	is_wall(t_ray *obj, double x, double y)
{
	int	row;
	int	clm;
	int	i;

	i = 0;
	clm = floor (x / 32);
	row = floor (y / 32);
	if (obj->game_map[row][clm] == '1')
		i++;
	clm = floor (obj->plays->new_x / 32);
	if (obj->game_map[row][clm] == '1')
		i++;
	clm = floor (x / 32);
	row = floor (obj->plays->new_y / 32);
	if (obj->game_map[row][clm] == '1')
		i++;
	if (i > 0)
		return (-1);
	return (0);
}

// void	left(t_ray *obj)
// {
// 	double	old_x;
// 	double	old_y;

// 	old_x = obj->plays->x_play;
// 	old_y = obj->plays->y_play;
// 	if (obj->plays->left_walk == 1)
// 	{
// 		obj->plays->fake_angle = obj->plays->rot_ang - (M_PI / 2);
// 		obj->plays->x_play += cos(obj->plays->fake_angle);
// 		obj->plays->y_play += sin(obj->plays->fake_angle);
// 		if ((is_wall (obj, obj->plays->x_play, obj->plays->y_play) == -1))
// 		{
// 			obj->plays->x_play = old_x;
// 			obj->plays->y_play = old_y;
// 		}
// 	}
// }

// void	right(t_ray *obj)
// {
// 	double	old_x;
// 	double	old_y;

// 	old_x = obj->plays->x_play;
// 	old_y = obj->plays->y_play;
// 	if (obj->plays->right_walk == 1)
// 	{
// 		obj->plays->fake_angle = obj->plays->rot_ang + (M_PI / 2);
// 		obj->plays->x_play += cos(obj->plays->fake_angle);
// 		obj->plays->y_play += sin(obj->plays->fake_angle);
// 		if ((is_wall (obj, obj->plays->x_play, obj->plays->y_play) == -1))
// 		{
// 			obj->plays->x_play = old_x;
// 			obj->plays->y_play = old_y;
// 		}
// 	}
// }

void	make_valus(t_play *blanka, t_ray *obj)
{
	double	movestep;

	(void) obj;
	movestep = blanka->walk_d * blanka->move_speed / 16 ;
	left (obj);
	right (obj);
	blanka->rot_ang += blanka->turn_d * blanka->rotation_speed;
	blanka->new_x = blanka->x_play;
	blanka->new_y = blanka->y_play;
	blanka->x_play += cos(blanka->rot_ang) * movestep;
	blanka->y_play += sin(blanka->rot_ang) * movestep;
	if ((is_wall (obj, blanka->x_play, blanka->y_play) == -1))
	{
		blanka->x_play = blanka->new_x;
		blanka->y_play = blanka->new_y;
	}
}
