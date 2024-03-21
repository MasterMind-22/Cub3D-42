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

	clm = floor (x / GRID_SIZE);
	row = floor (y / GRID_SIZE);
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
	clm = floor (x / GRID_SIZE);
	row = floor (y / GRID_SIZE);
	if (obj->game_map[row][clm] == '1')
		i++;
	clm = floor (obj->plays->new_x / GRID_SIZE);
	if (obj->game_map[row][clm] == '1')
		i++;
	clm = floor (x / GRID_SIZE);
	row = floor (obj->plays->new_y / GRID_SIZE);
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

void	norm_rot_angle(double *rot)
{
	*rot = fmod (*rot, 2 * M_PI);
	if (*rot < 0)
		*rot = (2 * M_PI) + *rot;
}

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
	// printf ("b = %f\n", blanka->rot_ang);
	norm_rot_angle (&blanka->rot_ang);
	// printf ("a = %d\n", is_ray_right (blanka->rot_ang));
	// if (is_ray_down (blanka->rot_ang) == 1)
	// {
	// 	if ((is_wall (obj, blanka->x_play, blanka->y_play - 5) == -1))
	// 	{
	// 		printf ("0\n");
	// 		blanka->x_play = blanka->new_x;
	// 		blanka->y_play = blanka->new_y;
	// 	}
	// }
	// if (is_ray_up (blanka->rot_ang) == 0)
	// {
	// 	if ((is_wall (obj, blanka->x_play, blanka->y_play - 5) == -1))
	// 	{
	// 		printf ("0\n");
	// 		blanka->x_play = blanka->new_x;
	// 		blanka->y_play = blanka->new_y;
	// 	}
	// }
	int i = 0;
	int j = 0;
	if (is_ray_down (blanka->rot_ang) == 1 && blanka->walk_d == 1)
	{
		// printf ("up and forward\n");
		i = 5;
		j = 0;
	}
	else if (is_ray_down (blanka->rot_ang) == 1 &&  blanka->walk_d == -1)
	{
		// printf ("down and back\n");
		i = -5;
		j = 0;
	}
	else if (is_ray_down (blanka->rot_ang) == 0 && blanka->walk_d == 1)
	{
		// printf ("down and forward\n");
		i = -5;
		j = 0;
	}
	else if (is_ray_down (blanka->rot_ang) == 0 &&  blanka->walk_d == -1)
	{
		// printf ("up and forward\n");
		i = 5;
		j = 0;
	}
	if ((is_wall (obj, blanka->x_play - j, blanka->y_play - i ) == -1))
		{
			// if (is_ray_down (blanka->rot_ang) == 1)
			// 	blanka->y_play -= 5;
			// printf ("1\n");
			blanka->x_play = blanka->new_x;
			blanka->y_play = blanka->new_y;
		}
	// #############################################################################################################################################
	if (is_ray_right (blanka->rot_ang) == 1 && blanka->walk_d == 1)
	{
		printf ("right and forward\n");
		i = 0;
		j = -5;
	}
	if (is_ray_right (blanka->rot_ang) == 1 && blanka->walk_d == -1)
	{
		printf ("right and back\n");
		i = 0;
		j = -3;
	}
	if (is_ray_right (blanka->rot_ang) == 0 && blanka->walk_d == 1)
	{
		printf ("left and forward\n");
		i = 0;
		j = 5;
	}
	if (is_ray_right (blanka->rot_ang) == 0 && blanka->walk_d == -1)
	{
		printf ("left and back\n");
		i = 0;
		j = -5;
	}
		if ((is_wall (obj, blanka->x_play - j, blanka->y_play - i ) == -1))
		{
			// if (is_ray_down (blanka->rot_ang) == 1)
			// 	blanka->y_play -= 5;
			// printf ("1\n");
			blanka->x_play = blanka->new_x;
			blanka->y_play = blanka->new_y;
		}
	// }
}
