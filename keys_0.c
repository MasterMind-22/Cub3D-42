/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:28:57 by momihamm          #+#    #+#             */
/*   Updated: 2024/03/06 19:30:17 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	close_the_win(void)
{
	exit (0);
}

int	is_ray_hit_wall(t_ray *obj, double x, double y)
{
	int	row;
	int	clm;
	int	i;

	i = 0;
	clm = floor (x / 32);
	row = floor (y / 32);
	// printf ("444444444\n");
	if (obj->game_map[row][clm] == '1')
	{
		// printf ("##############\t%c\t#####row %d  ######clm  %d######\n", obj->game_map[row][clm], row, clm);
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
	clm = round ((x - 0) / 32);
	row = round ((y - 0) / 32);
	// printf ("444444444\n");
	if (obj->game_map[row][clm] == '1')
		i++;
		// printf ("55555555555555\n");
	clm = round (obj->plays->new_x / 32);
	if (obj->game_map[row][clm] == '1')
		i++;
		// printf ("6666666666666666\n");
	clm = round ((x - 0) / 32);
	row = round (obj->plays->new_y / 32);
	if (obj->game_map[row][clm] == '1')
		i++;
		// printf ("7777777777777\n");
	if (i > 0)
		return (-1);
	return (0);
}

void	make_valus(t_play *blanka, t_ray *obj)
{
	double	movestep;

	(void) obj;
	blanka->rot_ang += blanka->turn_d * blanka->rotation_speed;
	movestep = blanka->walk_d * blanka->move_speed / 16;
	blanka->new_x = blanka->x_play;
	blanka->new_y = blanka->y_play;
	blanka->x_play += cos(blanka->rot_ang) * movestep;
	blanka->y_play += sin(blanka->rot_ang) * movestep;
	// printf ("ana zojk\n");
	if ((is_wall (obj, blanka->x_play, blanka->y_play) == -1))
	{
			printf ("***************************************************************\n");
		blanka->x_play = blanka->new_x;
		blanka->y_play = blanka->new_y;
		blanka->i_am_wall = 1;
	}
	if ((is_wall (obj, blanka->x_play, blanka->y_play) == 0))
		blanka->i_am_wall = 0;
	// printf ("%d\n", blanka->i_am_wall);
}

int	ft_mover(int events, void *object)
{
	t_ray	*obj;
	// t_cast *ptr;

	obj = (t_ray *)object;
	// ptr = obj->dataray;
	// int i =0;
	if (events == 53)
	{
		// printf ("*********************************************\n");
		// while (ptr != NULL)
		// {
		// 	printf ("this ray is %d\n{", i);
		// 	printf ("first_hit_x = %f\n", obj->dataray->first_hit_x);
		// 	printf ("first_hit_y = %f\n", obj->dataray->first_hit_y);
		// 	printf ("hor_massafa = %f\n", obj->dataray->hor_massafa);
		// 	printf ("vir_massafa = %f\n", obj->dataray->vir_massafa);
		// 	printf ("massafa = %f}\n", obj->dataray->massafa);
		// 	ptr++;
		// 	i++;
		// }
		// printf ("num of rays %d\n", obj->plays->num_of_rays);
		close_the_win ();
	}
	if (events == 124 || events == 2)
		obj->plays->turn_d = 0;
	if (events == 123 || events == 0)
		obj->plays->turn_d = 0;
	if (events == 126 || events == 13)
		obj->plays->walk_d = 0;
	if (events == 125 || events == 1)
		obj->plays->walk_d = 0;
	return (0);
}

int	ft_move(int events, void *object)
{
	t_ray	*obj;
	// t_cast *ptr;

	obj = (t_ray *) object;
	// ptr = obj->dataray;
	// int i =0;
	if (events == 53)
	{
		// printf ("*********************************************\n");
		// while (ptr != NULL && i < obj->plays->num_of_rays)
		// {
		// 	printf ("kkkk this ray is %d\n{", i);
		// 	printf ("kkkk first_hit_x = %f\n", obj->dataray->first_hit_x);
		// 	printf ("kkkk first_hit_y = %f\n", obj->dataray->first_hit_y);
		// 	printf ("kkkk hor_massafa = %f\n", obj->dataray->hor_massafa);
		// 	printf ("kkkk vir_massafa = %f\n", obj->dataray->vir_massafa);
		// 	printf ("kkkk massafa = %f}\n", obj->dataray->massafa);
		// 	ptr++;
		// 	i++;
		// }
		// printf ("num of rays %d\n", obj->plays->num_of_rays);
		// close_the_win ();
		close_the_win ();
	}
	if (events == 124 || events == 2)
		obj->plays->turn_d = 1;
	if (events == 123 || events == 0)
		obj->plays->turn_d = -1;
	if (events == 126 || events == 13)
		obj->plays->walk_d = 1;
	if (events == 125 || events == 1)
		obj->plays->walk_d = -1;
	return (0);
}
